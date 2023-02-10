#include "YonemaEnginePreCompile.h"
#include "PlayerLevelObserver.h"
#include "../ObservablePlayer.h"
#include "../../../CSV/CSVManager.h"
#include "../../../GameLog/GameLog.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			namespace {

				constexpr const wchar_t* kExpTableCSVFilePath = L"Assets/CSV/Player/ExpTable.csv";	//経験値テーブルのCSVのファイルパス
			}

			void CPlayerLevelObserver::InitSub(CObservablePlayer* observablePlayer) {

				//経験値テーブルのCSVをロード。
				nsCSV::CCsvManager csvManager;
				csvManager.LoadCSV(kExpTableCSVFilePath);

				//経験値テーブルを作成。
				for (const auto& expDataStr : csvManager.GetCsvData()) {

					std::vector<int> expData;

					for (const auto& expDataStrDetail : expDataStr) {

						expData.emplace_back(std::stoi(expDataStrDetail));
					}

					//取得した情報をリストに追加。
					m_expTable.emplace_back(expData);
				}

				//現在のプレイヤーのレベルを取得。
				m_oldPlayerLevel = observablePlayer->GetLevel();
			}

			void CPlayerLevelObserver::Update(CObservablePlayer* observablePlayer) {

				//経験値を取得。
				int exp = observablePlayer->GetExp();

				//レベルを取得。
				int level = observablePlayer->GetLevel();

				//経験値テーブルをレベルの場所から順に参照。
				for (int levelNum = level; levelNum < m_expTable.size(); levelNum++) {

					//比較経験値までスキップ。
					if (m_expTable[levelNum][static_cast<int>(EnExpTableVectorInfo::enNeedExp)] <= exp) {

						//レベルを一時保存。
						level = m_expTable[levelNum][static_cast<int>(EnExpTableVectorInfo::enLevel)];

						//次へ。
						continue;
					}

					//前回より上のレベルの経験値に到達しているなら。
					if (level > m_oldPlayerLevel) {

						//レベルアップ。
						observablePlayer->SetLevel(level);

						std::string levelUpText = "レベルが";
						levelUpText += std::to_string(level);
						levelUpText += "に上がった!";

						//レベルアップテキストを表示。
						nsGameLog::CGameLog::GetInstance()->AddGameLog(levelUpText);
					}

					//終了。
					return;
				}
			}
		}
	}
}