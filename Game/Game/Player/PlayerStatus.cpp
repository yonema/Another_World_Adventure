#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const wchar_t* kPlayerStatusCSVFilePath = L"Assets/CSV/Player/Player_Status.csv";	//プレイヤーステータスのCSVのファイルパス
			constexpr float kPlayerWinceDelimiter = 30.0f;	//プレイヤーのひるみ値の区切り（％）
			constexpr float kPerMax = 100.0f;			//最大％
		}

		void CPlayerStatus::Init() {

			//ステータスロード処理。
			LoadStatus();

#ifdef _DEBUG

			m_attack = 2.0f;

			m_intelligence = 2.0f;

			m_defence = 2.0f;
			m_mind = 2.0f;
#endif
			
		}

		void CPlayerStatus::LoadStatus() {

			//CSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kPlayerStatusCSVFilePath);

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

						//HPを取得。
						m_HP = std::stof(value);
					}
					else if (title == "MAXHP") {

						//最大HPを取得。
						m_maxHP = std::stof(value);
					}
					else if (title == "MP") {

						//MPを取得。
						m_MP = std::stof(value);
					}
					else if (title == "MAXMP") {

						//最大MPを取得。
						m_maxMP = std::stof(value);
					}
					else if (title == "SP") {

						//SPを取得。
						m_SP = std::stof(value);
					}
					else if (title == "MAXSP") {

						//最大SPを取得。
						m_maxSP = std::stof(value);
					}
					else if (title == "GG") {

						//ガードゲージの値を取得。
						m_guardGaugeValue = std::stof(value);
					}
					else if (title == "MAXGG") {

						//ガードゲージの最大値を取得。
						m_maxGuardGaugeValue = std::stof(value);
					}
					else if (title == "WINCE") {

						//ひるみ値を取得。
						m_winceValue = std::stof(value);
					}

					//プレイヤーのひるみ値の区切りを設定。
					m_winceDelimiter = m_maxHP * kPlayerWinceDelimiter / kPerMax;
				}
			}
		}

		void CPlayerStatus::HealHP(float value) {

			//HPを上昇させる。
			m_HP += value;

			//最大HPを超えているなら。
			if (m_HP > m_maxHP) {

				//最大HPと同じに設定する。
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(float value) {

			//HPを減少させる。
			m_HP -= value;

			//0未満になったら0に設定する。
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}

		void CPlayerStatus::HealMP(float value) {

			//MPを上昇させる。
			m_MP += value;

			//最大MPを超えているなら。
			if (m_MP > m_maxMP) {

				//最大MPと同じに設定する。
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(float value) {

			//MPを減少させる。
			m_MP -= value;

			//0未満になったら0に設定する。
			if (m_MP < 0.0f) {

				m_MP = 0.0f;
			}
		}

		void CPlayerStatus::HealSP(float value) {

			//SPを上昇させる。
			m_SP += value;

			//最大SPを超えているなら。
			if (m_SP > m_maxSP) {

				//最大SPと同じに設定する。
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(float value) {

			//SPを減少させる。
			m_SP -= value;

			//0未満になったら0に設定する。
			if (m_SP < 0.0f) {

				m_SP = 0.0f;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(float value) {

			//ガードゲージの値を上昇させる。
			m_guardGaugeValue += value;

			//ガードゲージの最大値を超えているなら。
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//ガードゲージの最大値と同じに設定する。
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(float value) {

			//ガードゲージの値を減少させる。
			m_guardGaugeValue -= value;

			//0未満になったら0に設定する。
			if (m_guardGaugeValue < 0.0f) {

				m_guardGaugeValue = 0.0f;
			}
		}
	}
}