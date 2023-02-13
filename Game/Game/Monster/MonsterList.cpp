#include "MonsterList.h"
#include "Monster.h"
#include "../CSV/CSVManager.h"
#include "../Utils/StringManipulation.h"
#include "MonsterAnimation.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr const wchar_t* const kMonsterNameCSVFilePath = L"Assets/CSV/Monsters/MonsterList.csv";		//モンスターの名前のリストのCSVのファイルパス
		}

		void CMonsterList::CreateMonsterList() {

			//モンスターの名前のリストを読み込む。
			nsCSV::CCsvManager monsterNameCsvManager;
			monsterNameCsvManager.LoadCSV(kMonsterNameCSVFilePath);

			//モンスターデータの雛形を生成。
			SMonsterInitData monsterInitData;

			//モンスターの名前からモンスター情報を読み込み、保持する。
			for (const auto& monsterList : monsterNameCsvManager.GetCsvData()) {

				//見出しを取得。
				std::string title = monsterList[0];

				if (title == "*") {

					//モンスターデータを追加。
					AddMonsterInitData(monsterInitData);

					//モンスターデータを初期化。
					SMonsterInitData monsterInitDataBase;
					monsterInitData = monsterInitDataBase;

					//次へ。
					continue;
				}

				if (title == "NAME") {

					//名前を設定。
					monsterInitData.name = monsterList[1];
				}
				
				if (title == "DROPEXP") {

					//獲得経験値量を設定。
					monsterInitData.dropExp = std::stoi(monsterList[1]);
				}

				if (title == "DROPITEM") {

					//ドロップアイテムを設定。
					monsterInitData.dropMaterialItemList.emplace_back(monsterList[1]);
				}

				//モデルのファイルパスを設定。
				monsterInitData.modelFilePath = "Assets/Models/Monsters/";
				monsterInitData.modelFilePath += monsterInitData.name;
				monsterInitData.modelFilePath += ".fbx";

				//アニメーション情報が入ったCSVファイルのパスを設定。
				std::string animCSVFilePath = "Assets/CSV/Monsters/";
				animCSVFilePath += monsterInitData.name + "/";
				animCSVFilePath += monsterInitData.name + "_Animation.csv";

				//アニメーションイベント情報が入ったCSVファイルのパスを設定。
				std::string animEventCSVFilePath = "Assets/CSV/Monsters/";
				animEventCSVFilePath += monsterInitData.name + "/";
				animEventCSVFilePath += monsterInitData.name + "_AnimationEvent.csv";

				//アニメーションをロード。
				CMonsterAnimation monsterAnimation;
				monsterAnimation.LoadAnimation(
					monsterInitData.name,
					nsUtils::GetWideStringFromString(animCSVFilePath).c_str(),
					nsUtils::GetWideStringFromString(animEventCSVFilePath).c_str()
				);

				//アニメーションデータのリストを取得、設定。
				monsterInitData.animDataList = monsterAnimation.GetAnimDataList();

				//アニメーションのファイルパスのリストを取得、設定。
				monsterInitData.animationFilePath = monsterAnimation.GetAnimFilePathArray();
			}
		}

		CMonster* CMonsterList::CreateMonster(const std::string& monsterName) {

			CMonster* monster = nullptr;
			//モンスターのリストを順に参照。
			for (const auto& monsterData : m_monsterDataList) {

				//同じ名前のモンスターを検索。
				if (monsterData.name == monsterName) {

					//モンスターを生成。
					monster = NewGO<CMonster>(nsMonster::CMonster::m_kObjName_Monster);
					monster->Create(monsterData);
				}
			}

			//モンスターが見つからなかったら。
			if (monster == nullptr) {

				std::string errMsg = "モンスターの検索に失敗しました。 : ";
				errMsg += monsterName;
				nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errMsg).c_str());
			}

			//モンスターをリターン。
			return monster;
		}
	}
}