#include "MonsterPopManager.h"
#include "MonsterPopPoint.h"

namespace nsAWA
{
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			const wchar_t* const CMonsterPopManager::m_kCsvFilePath =
				L"Assets/CSV/Monsters/MonsterPopTable.csv";

			const char* const CMonsterPopManager::
				m_kAreaNameArray[static_cast<int>(EnAreaType::enNum)] =
			{
				"Meadow",
				"Mountain",
				"Forest"
			};

			const char* const CMonsterPopManager::m_kMonsterPopPrefix = "MonsterPop_";


			bool CMonsterPopManager::Start()
			{

				return true;
			}

			void CMonsterPopManager::OnDestroy()
			{
				for (auto& popPoint : m_popPointList)
				{
					DeleteGO(popPoint);
					popPoint = nullptr;
				}
				m_popPointList.clear();

				return;
			}

			void CMonsterPopManager::Update(float deltaTime)
			{

				return;
			}

			CMonsterPopManager::CMonsterPopManager()
			{
				// 生成された瞬間に行いたい処理(Start()だと遅い場合)

				LoadData();

				CMonsterPopPoint::SetPopManagerRef(this);

				return;
			}


			void CMonsterPopManager::GenerateMonsterPopPoint(
				const std::string& pointName, const CVector3& pos)
			{
				const char* searchName = pointName.c_str();
				searchName += strlen(m_kMonsterPopPrefix);

				// エリア取得
				int areaIdx = 0;
				for (areaIdx = 0; areaIdx < static_cast<int>(EnAreaType::enNum); areaIdx++)
				{
					if (nsUtils::ForwardMatchName(searchName, m_kAreaNameArray[areaIdx]))
					{
						break;
					}
				}

				if (areaIdx >= static_cast<int>(EnAreaType::enNum))
				{
					MessageErrorLevelData(pointName, "エリア指定の値が不正です。");
					return;
				}

				searchName += strlen(m_kAreaNameArray[areaIdx]) + strlen("_");

				// ポイント取得
				int point = atoi(searchName);
				if (point <= 0)
				{
					MessageErrorLevelData(pointName, "ポイント指定の値が数値ではありません。");
					return;
				}

				auto areaToPointItr = m_monsterPopInfoTable.find(m_kAreaNameArray[areaIdx]);
				if (areaToPointItr == m_monsterPopInfoTable.end())
				{
					MessageErrorLevelData(pointName, "レベルで指定されたエリアが、魔物発生テーブルのcsvデータから読み込まれていません。");
					return;
				}

				auto pointToInfoItr = areaToPointItr->second.find(point);
				if (pointToInfoItr == areaToPointItr->second.end())
				{
					MessageErrorLevelData(pointName, "レベルで指定されたポイントが、魔物発生テーブルのcsvデータから読み込まれていません。");
					return;
				}


				auto* popPoint = NewGO<CMonsterPopPoint>(pointName.c_str());
				popPoint->Init(pointToInfoItr->second, pos);
				m_popPointList.emplace_back(popPoint);				

				return;
			}


			void CMonsterPopManager::LoadData()
			{
				m_scvManager.LoadCSV(m_kCsvFilePath);


				const auto& allData = m_scvManager.GetCsvData();

				for (const auto& rowData : allData)
				{
					// エラーチェック
					if (rowData.size() < 4)
					{
						MessageErrorCsvData(rowData, "データに最低限必要なデータが入っていません。");
						continue;
					}


					auto itr = rowData.begin();

					// エリア取得
					int areaIdx = 0;
					for (areaIdx = 0; areaIdx < static_cast<int>(EnAreaType::enNum); areaIdx++)
					{
						if (*itr == m_kAreaNameArray[areaIdx])
						{
							break;
						}
					}

					if (areaIdx >= static_cast<int>(EnAreaType::enNum))
					{
						MessageErrorCsvData(rowData, "エリア指定の値が不正です。");
						continue;
					}

					itr++;


					// ポイント取得
					int point = atoi(itr->c_str());
					if (point <= 0)
					{
						MessageErrorCsvData(rowData, "ポイント指定の値が数値ではありません。");
						continue;
					}

					itr++;

					MnsPopInfoList popInfoList = {};
					int checkPopRate = 0;

					while (itr != rowData.end())
					{
						std::list<const char*> nameList = {};
						int popRate = 0;

						while (popRate <= 0 && itr != rowData.end())
						{
							const char* charData = itr->c_str();
							popRate = atoi(charData);
							if (popRate <= 0)
							{
								nameList.emplace_back(charData);
							}

							itr++;
						}

						if (popRate <= 0)
						{
							MessageErrorCsvData(rowData, "発生率の値が不正です。");
							continue;
						}

						popInfoList.emplace_back(SMonsterPopInfo(nameList, popRate));
						checkPopRate += popRate;
					}


					if (checkPopRate != 100)
					{
						MessageErrorCsvData(rowData, "発生率の合計が100%になりません。");
						continue;
					}

					auto& pointToInfo = m_monsterPopInfoTable[m_kAreaNameArray[areaIdx]];

					if (pointToInfo.find(point) != pointToInfo.end())
					{
						MessageErrorCsvData(rowData, "同じポイントが複数設定されています。");
						continue;
					}

					auto& infoList = pointToInfo[point];

					infoList = popInfoList;

				}

				m_scvManager.ClearCSV();
				return;
			}



			void CMonsterPopManager::MessageErrorCsvData(
				const std::vector<std::string>& errorData,
				const char* message
			) const
			{
				std::string dataStr = {};
				for (const auto& data : errorData)
				{
					dataStr += data + ",";
				}

				MessageErrorData(
					"警告：魔物発生テーブルのcsvデータの不正",
					message,
					dataStr
				);

				return;
			}

			void CMonsterPopManager::MessageErrorLevelData(
				const std::string& errorData,
				const char* message
			)const
			{
				MessageErrorData(
					"警告：魔物発生のレベルデータの不正",
					message,
					errorData
				);

				return;
			}

			void CMonsterPopManager::MessageErrorData(
				const char* preMessage,
				const char* message,
				const std::string& errorData
			) const
			{
				std::string str = preMessage;

				str += '\n';
				str += message;

				str += "\n[";
				str += errorData;
				str += "]";

				auto wstr = nsUtils::GetWideStringFromString(str);
				nsGameWindow::MessageBoxWarning(wstr.c_str());

				return;
			}


		}
	}
}