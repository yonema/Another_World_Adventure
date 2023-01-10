#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"

#include "../../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr const wchar_t* const kPlayerAnimationCSVFilePath = L"Assets/CSV/Animation.csv";	//プレイヤーのアニメーションのCSVファイルパス
				constexpr const wchar_t* const kPlayerAnimationEventCSVFilePath = L"Assets/CSV/AnimationEvent.csv";	//プレイヤーのアニメーションのイベントのCSVファイルパス
				constexpr int kCSVTitleData = 0;		//CSVデータの見出し情報。
			}

			//アニメーションのファイルパスを定義。
			std::string CPlayerAnimation::
				m_animFilePaths[static_cast<int>(EnAnimName::enNum)] = {};

			void CPlayerAnimation::Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction) {

				//アニメーションデータを読み込む。
				LoadAnimation();

				//各アニメーションを初期化。
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)]->Init(m_animDataList);

				//アニメーションイベントクラスを初期化。
				m_animationEvent.Init(player, playerInput, playerAction);
#ifdef _DEBUG
				//剣タイプに設定。
				m_type = EnAnimType::enSword;
#endif // _DEBUG

			}

			void CPlayerAnimation::SetPlayerModelAndAnimEvent(CModelRenderer* playerModel) {

				//プレイヤーモデルを設定。
				m_playerModel = playerModel;

				for (const auto& animData : m_animDataList) {
				
					//このアニメーションのイベント数を伝える。
					m_playerModel->ReserveAnimationEventFuncArray(static_cast<int>(animData.animName), static_cast<int>(animData.animationEvent.size()));
				
					//アニメーションイベントを順に参照。
					for (const auto& animEventData : animData.animationEvent) {
					
						//アニメーションイベントを追加。
						m_playerModel->AddAnimationEventFunc(
							static_cast<unsigned int>(animData.animName),
							[&]() {m_animationEvent.GetAnimationEvent(
								animEventData.eventName,
								animEventData.eventData);
							}
						);
					}
				}
			}

			void CPlayerAnimation::Release() {

			}

			void CPlayerAnimation::Update(bool changeState, EnPlayerState playerState) {

				//ステートに変更があったか。
				if (changeState) {
					
					//ステートに対応するアニメーションを流す。
					PlayAnimation(playerState);
				}
			}

			void CPlayerAnimation::PlayAnimation(EnPlayerState playerState) {

				//アニメーションタイプからどのアニメーションクラスを使うか決める。
				switch (m_type) {

					//剣アニメーションクラス。
				case EnAnimType::enSword:

					//更新。
					m_playerAnimation[static_cast<int>(EnAnimType::enSword)]->UpdateAnimation(m_playerModel, playerState);
					break;
				}
			}

			void CPlayerAnimation::LoadAnimation() {

				//CSV管理クラスを生成。
				nsCSV::CCsvManager csvManager;

				//プレイヤーアニメーションのCSVを読み込む。
				csvManager.LoadCSV(kPlayerAnimationCSVFilePath);

				//データカウントを初期化。
				int dataIndex = 0;

				std::string topData = "";

				//アニメーションデータの雛形を生成。
				SAnimData animDataBase;

				//アニメーション情報を取り出す。
				for (const auto& animData : csvManager.GetCsvData()) {

					if (animData[kCSVTitleData] == "*") {

						//アニメーション情報の終端なので情報を追加。

						//データを格納。
						m_animDataList.emplace_back(animDataBase);

						//データを進める。
						dataIndex++;

						//アニメーションデータの雛形を初期化。
						SAnimData clearData;
						animDataBase = clearData;

						//次へ。
						continue;
					}

					if (animData[kCSVTitleData] == "NAME") {

						//ファイルパスを取得、設定。
						m_animFilePaths[dataIndex] += "Assets/Animations/Player/";
						m_animFilePaths[dataIndex] += animData[1];
						m_animFilePaths[dataIndex] += ".fbx";

						//番号を取得。
						animDataBase.animName = static_cast<EnAnimName>(dataIndex);
					}

					if (animData[kCSVTitleData] == "SPEED") {

						//速さを取得。
						animDataBase.speed = std::stof(animData[1]);
					}

					if (animData[kCSVTitleData] == "LOOP") {

						//ループフラグを取得。
						animDataBase.enLoopFlag = animData[1] == "TRUE" ? true : false;
					}

					if (animData[kCSVTitleData] == "EVENT") {

						SAnimationEventData animEventData;

						//イベントを取得。
						animEventData.eventName = animData[1];
						animEventData.hasEventMaterial = animData[2] == "TRUE" ? true : false;

						animDataBase.animationEvent.emplace_back(animEventData);
					}
				}

				//CSVデータを初期化。
				csvManager.ClearCSV();

				//アニメーションイベントのCSVを読み込む。
				csvManager.LoadCSV(kPlayerAnimationEventCSVFilePath);

				//アニメーションイベントを追加するための雛形を初期化。
				std::list<std::list<std::vector<std::string>>> animEventDataList;
				std::list<std::vector<std::string>> animEventData;

				//アニメーションイベントのデータをリスト化。
				for (const auto& animEventStr : csvManager.GetCsvData()) {

					//一つのデータの終端なら。
					if (animEventStr[0] == "*") {

						//リストにイベントデータを追加。
						animEventDataList.emplace_back(animEventData);

						//雛形のデータを破棄。
						animEventData.clear();

						//次へ。
						continue;
					}

					//イベントの情報を追加。
					animEventData.emplace_back(animEventStr);
				}

				//アニメーションデータを順に参照。
				for (auto& animData : m_animDataList) {

					//アニメーションイベントを順に参照。
					for (auto& animEvent : animData.animationEvent) {

						//イベント情報が必要ないなら。
						if (!animEvent.hasEventMaterial) {

							//次のイベントへ。
							continue;
						}
						//イベントに情報が必要なら。
						else {
							
							//アニメーションイベントデータの先頭情報を取り出す。
							auto animEventDataItr = animEventDataList.begin();

							//データを格納。
							animEvent.eventData = *animEventDataItr;

							//先頭情報を破棄。
							animEventDataList.erase(animEventDataItr);
						}
					}
				}
			}
		}
	}
}