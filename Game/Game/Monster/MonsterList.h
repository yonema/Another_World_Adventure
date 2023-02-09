#pragma once
#include "MonsterAnimation.h"

namespace nsAWA {

	namespace nsMonster {

		//前方宣言
		class CMonster;
		struct SAnimData;

		//モンスターデータ
		struct SMonsterInitData {

			std::string name = "NoName";				//名前
			int dropExp = 0;							//獲得経験値量
			std::string modelFilePath = "NoFilePath";	//モデルのファイルパス
			std::vector<std::string> animationFilePath;	//アニメーションのファイルパスのリスト
			std::vector<SAnimData> animDataList;		//アニメーションデータ
		};
		//モンスターリスト
		class CMonsterList : public nsUtils::SNoncopyable {

			
		public:
			static CMonsterList* GetInstance() {

				//インスタンスを生成。
				static CMonsterList* instance = new CMonsterList;

				//インスタンスをリターン。
				return instance;
			}

			static void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void CreateMonsterList();

			CMonster* CreateMonster(const std::string& monsterName);

		private:
			void AddMonsterInitData(const SMonsterInitData& monsterData) {

				//モンスターデータを追加。
				m_monsterDataList.emplace_back(monsterData);
			}

		private:

			std::list<SMonsterInitData> m_monsterDataList;	//モンスターデータのリスト
		};
	}
}