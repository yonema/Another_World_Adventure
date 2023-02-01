#include "YonemaEnginePreCompile.h"
#include "ActiveSkillList.h"
#include "../CSV/CSVManager.h"
#include "../Skill/ActiveSkill.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr const wchar_t* kActiveSkillCSVFilePath = L"Assets/CSV/Player/ActiveSkillList.csv";	//アクティブスキルのCSVファイルパス
		}

		void CActiveSkillList::LoadActiveSkillList() {

			//アクティブスキルのリストのCSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kActiveSkillCSVFilePath);

			//アクティブスキルのデータを順に参照。
			for (const auto& lineData : csvManager.GetCsvData()) {

				//スキルタイプを取得。
				std::string type = lineData[0];

				//名前を取得。
				std::string name = lineData[1];

				//消費MPを取得。
				float useMP = std::stof(lineData[2]);

				//アクティブスキルのデータを設定。
				SActiveSkillData activeSkillData;
				activeSkillData.type = type;
				activeSkillData.name = name;
				activeSkillData.useMP = useMP;

				//アクティブスキルのデータをリストに追加。
				AddActiveSkill(activeSkillData);
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

			//生成したアクティブスキルをリターン。
			return activeSkill;
		}
	}
}