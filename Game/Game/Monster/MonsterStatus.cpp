#include "YonemaEnginePreCompile.h"
#include "MonsterStatus.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsMonster {

		void CMonsterStatus::Init(const std::string& monsterName) {

			//ステータス情報が入ったCSVファイルのパスを設定。
			std::string monsterStatusCSVFilePath = "Assets/CSV/Monsters/";
			monsterStatusCSVFilePath += monsterName + "/";
			monsterStatusCSVFilePath += monsterName + "_Status.csv";

			//CSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(nsUtils::GetWideStringFromString(monsterStatusCSVFilePath).c_str());

			//CSVデータを順に参照。
			for (const auto& lineData : csvManager.GetCsvData()) {

				//見出し情報を取得。
				std::string title = lineData[0];

				//値を取得。
				std::string value = lineData[1];

				//データを取得。
				{
					if (title == "LEVEL") {

						//レベルを取得。
						m_level = std::stoi(value);
					}
					else if (title == "HP") {

						//最大HPとHPを取得。
						m_maxHP = std::stof(value);
						m_HP = std::stof(value);
					}
					else if (title == "ATK") {

						//物理攻撃力を取得。
						m_attack = std::stof(value);
					}
					else if (title == "INT") {

						//魔法攻撃力を取得。
						m_intelligence = std::stof(value);
					}
					else if (title == "DEF") {

						//物理防御力を取得。
						m_defence = std::stof(value);
					}
					else if (title == "MND") {

						//魔法防御力を取得。
						m_mind = std::stof(value);
					}
					else if (title == "WINCE") {

						//ひるみ値を取得。
						m_winceValue = 0.0f;
						m_winceDelimiter = std::stof(value);
					}
				}
			}
		}

		void CMonsterStatus::HealHP(float value) {

			//HPを上昇させる。
			m_HP += value;

			//最大HPを超えているなら。
			if (m_HP > m_maxHP) {

				//最大HPと同じに設定する。
				m_HP = m_maxHP;
			}
		}

		void CMonsterStatus::DamageHP(float value) {

			//HPを減少させる。
			m_HP -= value;

			//0未満になったら0に設定する。
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}
	}
}