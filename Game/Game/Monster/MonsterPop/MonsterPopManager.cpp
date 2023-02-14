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
				// �������ꂽ�u�Ԃɍs����������(Start()���ƒx���ꍇ)

				LoadData();

				CMonsterPopPoint::SetPopManagerRef(this);

				return;
			}


			void CMonsterPopManager::GenerateMonsterPopPoint(
				const std::string& pointName, const CVector3& pos)
			{
				const char* searchName = pointName.c_str();
				searchName += strlen(m_kMonsterPopPrefix);

				// �G���A�擾
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
					MessageErrorLevelData(pointName, "�G���A�w��̒l���s���ł��B");
					return;
				}

				searchName += strlen(m_kAreaNameArray[areaIdx]) + strlen("_");

				// �|�C���g�擾
				int point = atoi(searchName);
				if (point <= 0)
				{
					MessageErrorLevelData(pointName, "�|�C���g�w��̒l�����l�ł͂���܂���B");
					return;
				}

				auto areaToPointItr = m_monsterPopInfoTable.find(m_kAreaNameArray[areaIdx]);
				if (areaToPointItr == m_monsterPopInfoTable.end())
				{
					MessageErrorLevelData(pointName, "���x���Ŏw�肳�ꂽ�G���A���A���������e�[�u����csv�f�[�^����ǂݍ��܂�Ă��܂���B");
					return;
				}

				auto pointToInfoItr = areaToPointItr->second.find(point);
				if (pointToInfoItr == areaToPointItr->second.end())
				{
					MessageErrorLevelData(pointName, "���x���Ŏw�肳�ꂽ�|�C���g���A���������e�[�u����csv�f�[�^����ǂݍ��܂�Ă��܂���B");
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
					// �G���[�`�F�b�N
					if (rowData.size() < 4)
					{
						MessageErrorCsvData(rowData, "�f�[�^�ɍŒ���K�v�ȃf�[�^�������Ă��܂���B");
						continue;
					}


					auto itr = rowData.begin();

					// �G���A�擾
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
						MessageErrorCsvData(rowData, "�G���A�w��̒l���s���ł��B");
						continue;
					}

					itr++;


					// �|�C���g�擾
					int point = atoi(itr->c_str());
					if (point <= 0)
					{
						MessageErrorCsvData(rowData, "�|�C���g�w��̒l�����l�ł͂���܂���B");
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
							MessageErrorCsvData(rowData, "�������̒l���s���ł��B");
							continue;
						}

						popInfoList.emplace_back(SMonsterPopInfo(nameList, popRate));
						checkPopRate += popRate;
					}


					if (checkPopRate != 100)
					{
						MessageErrorCsvData(rowData, "�������̍��v��100%�ɂȂ�܂���B");
						continue;
					}

					auto& pointToInfo = m_monsterPopInfoTable[m_kAreaNameArray[areaIdx]];

					if (pointToInfo.find(point) != pointToInfo.end())
					{
						MessageErrorCsvData(rowData, "�����|�C���g�������ݒ肳��Ă��܂��B");
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
					"�x���F���������e�[�u����csv�f�[�^�̕s��",
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
					"�x���F���������̃��x���f�[�^�̕s��",
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