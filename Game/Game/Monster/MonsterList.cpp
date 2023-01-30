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

			//モンスターの名前からモンスター情報を読み込み、保持する。
			for (const auto& monsterList : monsterNameCsvManager.GetCsvData()) {

				for (const auto& monsterName : monsterList) {

					//モンスターデータの雛形を生成。
					SMonsterInitData monsterInitData;

					//名前を設定。
					monsterInitData.name = monsterName;

					monsterInitData.modelFilePath = "Assets/Models/Monsters/";
					monsterInitData.modelFilePath += monsterName;
					monsterInitData.modelFilePath += ".fbx";

					//アニメーション情報が入ったCSVファイルのパスを設定。
					std::string animCSVFilePath = "Assets/CSV/Monsters/";
					animCSVFilePath += monsterName + "/";
					animCSVFilePath += monsterName + "_Animation.csv";

					//アニメーションイベント情報が入ったCSVファイルのパスを設定。
					std::string animEventCSVFilePath = "Assets/CSV/Monsters/";
					animEventCSVFilePath += monsterName + "/";
					animEventCSVFilePath += monsterName + "_AnimationEvent.csv";

					//アニメーションをロード。
					CMonsterAnimation monsterAnimation;
					monsterAnimation.LoadAnimation(
						monsterName,
						nsUtils::GetWideStringFromString(animCSVFilePath).c_str(),
						nsUtils::GetWideStringFromString(animEventCSVFilePath).c_str()
					);

					//アニメーションデータのリストを取得、設定。
					monsterInitData.animDataList = monsterAnimation.GetAnimDataList();

					//アニメーションのファイルパスのリストを取得、設定。
					monsterInitData.animationFilePath = monsterAnimation.GetAnimFilePathArray();

					//モンスターデータを追加。
					AddMonsterInitData(monsterInitData);
				}
			}
		}

		CMonster* CMonsterList::CreateMonster(const std::string& monsterName) {

			CMonster* monster = nullptr;
			//モンスターのリストを順に参照。
			for (const auto& monsterData : m_monsterDataList) {

				//同じ名前のモンスターを検索。
				if (monsterData.name == monsterName) {

					//モンスターデータを初期化。
					SMonsterInitData monsterInitData;
					monsterInitData.name = monsterData.name;
					monsterInitData.animDataList = monsterData.animDataList;
					monsterInitData.animationFilePath = monsterData.animationFilePath;
					monsterInitData.modelFilePath = monsterData.modelFilePath;

					//モンスターを生成。
					monster = NewGO<CMonster>(nsMonster::CMonster::m_kObjName_Monster);
					monster->Create(monsterInitData);
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