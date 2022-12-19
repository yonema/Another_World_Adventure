#include "YonemaEnginePreCompile.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"

#include "../../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr const wchar_t* const kPlayerAnimationCSVFilePath = L"Assets/CSV/Animation.csv";	//プレイヤーのアニメーションのCSVファイルパス
			}

			//アニメーションのファイルパスを定義。
			std::string CPlayerAnimation::
				m_animFilePaths[static_cast<int>(EnAnimName::enNum)] = {};

			void CPlayerAnimation::Init(CPlayerInput* playerInput) {

				//アニメーションデータを読み込む。
				LoadAnimation();

				//各アニメーションを割り当てる。
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;

				//アニメーションイベントクラスを初期化。
				m_animationEvent.Init(playerInput);
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
					m_playerModel->ReserveAnimationEventFuncArray(static_cast<int>(animData.animName), animData.animationEvent.size());

					//アニメーションイベントを順に参照。
					for (const auto& animEventName : animData.animationEvent) {
					
						//アニメーションイベントを順に参照。
						m_playerModel->AddAnimationEventFunc(
							static_cast<unsigned int>(animData.animName),
							[&]() {m_animationEvent.GetAnimationEvent(animEventName); }
						);
					}
				}

				//m_playerModel->AddAnimationEventFunc(
				//	static_cast<unsigned int>(EnAnimName::enSword_UseItem),
				//	[&]() {m_animationEvent.CoolTimeOff(); }
				//);
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

				//アニメーション情報を取り出す。
				for (const auto& anim : csvManager.GetCsvData()) {

					//アニメーションデータの雛形を生成。
					SAnimData animData;

					//ファイルパスを取得。
					m_animFilePaths[dataIndex] += "Assets/Animations/";
					m_animFilePaths[dataIndex] += anim[static_cast<int>(EnAnimInfo::enFilePath)];
					m_animFilePaths[dataIndex] += ".fbx";

					//番号を取得。
					animData.animName = static_cast<EnAnimName>(dataIndex);

					//速度を取得。
					animData.speed = std::stof(anim[static_cast<int>(EnAnimInfo::enSpeed)]);

					//ループフラグの文字列を取得。
					std::string loopFlag = anim[static_cast<int>(EnAnimInfo::enLoopFlag)];

					//文字列からループフラグを設定。
					if (loopFlag == "TRUE") {

						animData.enLoopFlag = true;
					}
					else if (loopFlag == "FALSE") {

						animData.enLoopFlag = false;
					}
					else {
						nsGameWindow::MessageBoxError(L"アニメーションのループ情報が正しくありません。");
					}

					//アニメーションイベント情報を格納。
					for (int animationEvent = static_cast<int>(EnAnimInfo::enAnimationEvent); animationEvent < anim.size(); animationEvent++) {

						//リストに追加。
						animData.animationEvent.emplace_back(anim[animationEvent]);
					}

					//データを格納。
					m_animDataList.emplace_back(animData);

					//データカウントを進める。
					dataIndex++;
				}
			}
		}
	}
}