#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "PlayerAnimationEvent.h"
#include "PlayerAnimation.h"
#include "../PlayerAction.h"
#include "../../Skill/ActiveSkill.h"

#include "../../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr const wchar_t* const kPlayerAnimationCSVFilePath = L"Assets/CSV/Player/Test/Animation.csv";	//プレイヤーのアニメーションのCSVファイルパス
				constexpr const wchar_t* const kPlayerAnimationEventCSVFilePath = L"Assets/CSV/Player/Test/AnimationEvent.csv";	//プレイヤーのアニメーションのイベントのCSVファイルパス
				constexpr const float kCanPlayerInput = 0.001f;	//入力が判定される最低値
			}

			void CPlayerAnimation::Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction) {

				//アニメーションデータを読み込む。
				LoadAnimation();

				//アニメーションイベントクラスを初期化。
				m_animationEvent.Init(player, playerInput, playerAction, this);

				//剣タイプに設定。
				m_type = EnAnimType::enSword;

			}

			void CPlayerAnimation::SetPlayerModelAndAnimEvent(CModelRenderer* playerModel) {

				//プレイヤーモデルを設定。
				m_playerModel = playerModel;

				for (const auto& animData : m_animDataList) {
				
					//このアニメーションのイベント数を伝える。
					m_playerModel->ReserveAnimationEventFuncArray(animData.animNum, static_cast<int>(animData.animationEvent.size()));
				
					//アニメーションイベントを順に参照。
					for (const auto& animEventData : animData.animationEvent) {
					
						//アニメーションイベントを追加。
						m_playerModel->AddAnimationEventFunc(
							animData.animNum,
							[&]() {m_animationEvent.GetAnimationEvent(
								animEventData.eventName,
								animEventData.detailStr);
							}
						);
					}
				}
			}

			void CPlayerAnimation::Release() {

				//データを破棄。
				m_animDataList.clear();

				m_animFilePathArray.clear();
			}

			void CPlayerAnimation::Update(bool changeState, EnPlayerState playerState) {

				//ステートに変更があったか。
				if (changeState) {
					
					//ステートに対応するアニメーションを流す。
					PlayAnimation(playerState);
				}

				//アニメーションイベントを更新。
				m_animationEvent.Update();
			}

			void CPlayerAnimation::PlayAnimation(EnPlayerState playerState) {

				//ステートから対応アニメーションのindexを取得。
				const SAnimData& animationData = GetAnimationData(playerState);

				//対応するアニメーションがないなら。
				if (animationData.animNum == -1) {

					//再生できないので早期リターン。
					return;
				}
				else {

					//対応するアニメーションを再生。
					m_playerModel->PlayAnimationFromBeginning(
						animationData.animNum,
						animationData.speed,
						animationData.isLoopAnim
					);
				}
			}

			const SAnimData& CPlayerAnimation::GetAnimationData(EnPlayerState playerState) {

				std::string stateStr = "NoStr";

				//プレイヤーのタイプからアニメーションの先頭文字列を選択する。
				switch (m_type) {

				case EnAnimType::enSword:

					stateStr = "Sword_";
					break;
				case EnAnimType::enAxe:

					stateStr = "Axe_";
					break;
				case EnAnimType::enWand:

					stateStr = "Wand_";
					break;
				}

				//ステートを文字列に変換して合成。
				switch (playerState) {

				case EnPlayerState::enIdle:
					stateStr += "Idle";
					break;
				case EnPlayerState::enWalk:
					stateStr += "Walk";
					break;
				case EnPlayerState::enRun:
					stateStr += "Run";
					break;
				case EnPlayerState::enStep:
					stateStr += "ForwardStep";
					break;
				case EnPlayerState::enWeakAttack_A:
					stateStr += "WeakAttack_A";
					break;
				case EnPlayerState::enWeakAttack_B:
					stateStr += "WeakAttack_B";
					break;
				case EnPlayerState::enWeakAttack_C:
					stateStr += "WeakAttack_C";
					break;
				case EnPlayerState::enStrongAttack:
					stateStr += "StrongAttack";
					break;
				case EnPlayerState::enUseActiveSkill:

					//アクティブスキルならスキルの名前を設定。
					SetActiveSkillName(stateStr);
					break;
				case EnPlayerState::enDamage:
					stateStr += "Damage";
					break;
				case EnPlayerState::enDeath:
					stateStr += "Death";
					break;
				case EnPlayerState::enGuard:
					stateStr += "Guard";
					break;
				case EnPlayerState::enUseItem:
					stateStr += "UseItem";
					break;
				case EnPlayerState::enStun:
					stateStr += "Stun";
					break;
				}

				//アニメーションリストから対応するアニメーションの番号を検索。
				for (const auto& animation : m_animDataList) {

					//同じ名前のアニメーションが見つかった。
					if (animation.animName == stateStr) {

						//そのアニメーションをリターン。
						return animation;
					}
				}

				//見つからなかった。
				std::string errMsg = "対応するアニメーションが見つかりませんでした。 : ";
				errMsg += stateStr;
				nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errMsg).c_str());

				std::abort();
			}

			void CPlayerAnimation::SetActiveSkillName(std::string& name) {

				//アクティブスキルの名前を取得。
				if (m_activeSkill != nullptr) {

					if (m_activeSkill->GetType() == nsSkill::CActiveSkill::EnActiveSkillType::enMagic) {

						name = "Magic";

						//終了。
						return;
					}

					//アニメーションを指定するため、ファイルパスを取得。
					name = m_activeSkill->GetAnimationFilePath();

					//終了。
					return;
				}
				else {
#ifdef _DEBUG
					//見つからなかった。
					std::string errorMsg = "CPlayerAnimation : アクティブスキルの予約がされていません。";

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

					std::abort();
#endif // _DEBUG
				}
			}

			void CPlayerAnimation::LoadAnimation() {

				//CSV管理クラスを生成。
				nsCSV::CCsvManager csvManager;

				//プレイヤーアニメーションのCSVを読み込む。
				csvManager.LoadCSV(kPlayerAnimationCSVFilePath);

				//データカウントを初期化。
				int dataIndex = 0;

				//アニメーションデータの雛形を生成。
				SAnimData animDataBase;

				//アニメーション情報を取り出す。
				for (const auto& animData : csvManager.GetCsvData()) {

					//見出しを取得。
					std::string titleData = animData[0];

					if (titleData == "*") {

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

					if (titleData == "NAME") {

						//ファイルパスを取得、設定。
						std::string filePath = "Assets/Animations/Player/";
						filePath += animData[1];
						filePath += ".fbx";

						//アニメーションのファイルパスを配列に追加。
						m_animFilePathArray.emplace_back(filePath);

						//アニメーションの名前を取得。
						animDataBase.animName = animData[1];

						//番号を取得。
						animDataBase.animNum = dataIndex;
					}

					if (titleData == "SPEED") {

						//速さを取得。
						animDataBase.speed = std::stof(animData[1]);
					}

					if (titleData == "LOOP") {

						//ループフラグを取得。
						animDataBase.isLoopAnim = animData[1] == "TRUE" ? true : false;
					}

					if (titleData == "EVENT") {

						SAnimationEventData animEventData;

						//イベントを取得。
						animEventData.eventName = animData[1];
						animEventData.detailStr = animData[2];

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
			}
		}
	}
}