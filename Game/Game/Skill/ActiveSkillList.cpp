#include "YonemaEnginePreCompile.h"
#include "ActiveSkillList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr const wchar_t* kActiveSkillCSVFilePath = L"Assets/CSV/Player/ActiveSkillList.csv";	//アクティブスキルのCSVファイルパス
			constexpr const wchar_t* kActiveSkillAnimationEventCSVFilePath = L"Assets/CSV/Player/ActiveSkillAnimationEventList.csv";	//アクティブスキルのアニメーションイベントのCSVファイルパス
		}

		void CActiveSkillList::LoadActiveSkillList() {

			//アクティブスキルのリストのCSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kActiveSkillCSVFilePath);
			std::list<std::vector<std::string>> activeSkillDataStr = csvManager.GetCsvData();

			//アクティブスキルのデータを順に参照。
			for (const auto& lineData : activeSkillDataStr) {

				//スキルタイプを取得。
				std::string type = lineData[0];

				//名前を取得。
				std::string name = lineData[1];

				//消費MPを取得。
				float useMP = std::stof(lineData[2]);

				//アニメーションのファイルパスを取得。
				std::string animFilePath = lineData[3];

				//アクティブスキルのデータを設定。
				SActiveSkillData activeSkillData;
				activeSkillData.type = type;
				activeSkillData.name = name;
				activeSkillData.useMP = useMP;
				activeSkillData.animFilePath= animFilePath;

				//アクティブスキルのデータをリストに追加。
				AddActiveSkill(activeSkillData);
			}

			//アクティブスキルのアニメーションイベントのリストのCSVをロード。
			csvManager.ClearCSV();
			csvManager.LoadCSV(kActiveSkillAnimationEventCSVFilePath);
			std::list<std::vector<std::string>> activeSkillAnimationEventDataStr = csvManager.GetCsvData();

			std::list<CActiveSkill::SActiveSkillAnimData> activeSkillAnimDataList;
			CActiveSkill::SActiveSkillAnimData activeSkillAnimDataBase;
			std::list<std::vector<std::string>> animEventFeatureData;

			//アニメーションイベントのリストを順に参照。
			for (const auto& animEventData : activeSkillAnimationEventDataStr) {

				//見出しを取得。
				std::string title = animEventData[0];

				if (title == "*") {

					//アニメーションイベントの詳細を追加。
					activeSkillAnimDataBase.sAnimEventData = animEventFeatureData;

					//詳細を初期化。
					std::list<std::vector<std::string>> initFeatureData;
					animEventFeatureData = initFeatureData;

					activeSkillAnimDataList.emplace_back(activeSkillAnimDataBase);
					CActiveSkill::SActiveSkillAnimData initData;
					activeSkillAnimDataBase = initData;

					//次へ。
					continue;
				}

				if (title == "NAME") {

					activeSkillAnimDataBase.skillName = animEventData[1];
					
					//次へ。
					continue;
				}
				else if (title == "INDEX") {

					activeSkillAnimDataBase.index = animEventData[1];

					//次へ。
					continue;
				}
				else {

					animEventFeatureData.emplace_back(animEventData);

					//次へ。
					continue;
				}
			}

			//スキルデータにアニメーションデータを追加するため、リストを照らし合わせる。
			for (auto& skillList : m_activeSkillList) {

				for (const auto& skillAnim : activeSkillAnimDataList) {

					//同じ名前のスキルアニメーションデータが見つかったらコピー。
					if (skillList.name == skillAnim.skillName) {

						skillList.animDataList.emplace_back(skillAnim);
					}
				}
			}
		}

		const SActiveSkillData& CActiveSkillList::GetActiveSkillData(const std::string& activeSkillName) {

			//アクティブスキルのリストを順に参照。
			for (const auto& activeSkillData : m_activeSkillList) {

				//同じ名前のアクティブスキルが見つかったら。
				if (activeSkillData.name == activeSkillName) {

					//そのデータをリターン。
					return activeSkillData;
				}
			}

			//名前がリストに存在していないので警告を出力。
			std::string errorMsg = "検索された名前がリストにありません。 : ";
			errorMsg += activeSkillName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}

		CActiveSkill* CActiveSkillBuilder::CreateActiveSkill(const std::string& activeSkillName) {

			//名前からアクティブスキルのデータを取得。
			SActiveSkillData activeSkillData = CActiveSkillList::GetInstance()->GetActiveSkillData(activeSkillName);

			//アクティブスキルを生成。
			CActiveSkill* activeSkill = new CActiveSkill;

			//スキルタイプを取得。
			CActiveSkill::EnActiveSkillType type = CActiveSkill::EnActiveSkillType::enNone;
			if (activeSkillData.type == "Sword") {

				type = CActiveSkill::EnActiveSkillType::enSword;
			}
			else if (activeSkillData.type == "Axe") {

				type = CActiveSkill::EnActiveSkillType::enAxe;
			}
			else if (activeSkillData.type == "Wand") {

				type = CActiveSkill::EnActiveSkillType::enWand;
			}
			else if (activeSkillData.type == "Magic") {

				type = CActiveSkill::EnActiveSkillType::enMagic;
			}

			//各種設定。
			activeSkill->SetName(activeSkillData.name);
			activeSkill->SetUseMP(activeSkillData.useMP);
			activeSkill->SetType(type);
			activeSkill->SetAnimaitonFilePath(activeSkillData.animFilePath);
			activeSkill->SetAnimDataList(activeSkillData.animDataList);

			//生成したアクティブスキルをリターン。
			return activeSkill;
		}
	}
}