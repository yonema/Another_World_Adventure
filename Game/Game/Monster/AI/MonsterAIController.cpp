#include "YonemaEnginePreCompile.h"
#include "../Utils/StringManipulation.h"
#include "../Monster.h"
#include "MonsterAIController.h"
#include "../../CSV/CSVManager.h"
#include "AITask/AITaskBuilder.h"
#include "AITask/AITaskWait.h"
#include "AISequence.h"
#include "AISelector.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CMonsterAIController::Init(CMonster* owner) {

				//ゲームアクターを設定。
				m_owner = owner;

				//名前を取得。
				std::string monsterName = owner->GetName();

				//AI情報が入ったCSVのファイルパスを設定。
				std::string monsterStatusCSVFilePath = "Assets/CSV/Monsters/";
				monsterStatusCSVFilePath += monsterName + "/";
				monsterStatusCSVFilePath += monsterName + "_AI.csv";

				//CSVをロード。
				nsCSV::CCsvManager csvManager;
				csvManager.LoadCSV(nsUtils::GetWideStringFromString(monsterStatusCSVFilePath).c_str());

				//CSVデータを取得。
				AIPartsDataStr strData = csvManager.GetCsvData();

				//ビヘイビアツリーを構築。
				m_rootNode = CreateAIPart(strData);
			}

			void CMonsterAIController::Release() {

				if (m_rootNode != nullptr) {

					//ノードを破棄。
					m_rootNode->Release();
				}
			}

			CAIPart* CMonsterAIController::CreateAIPart(AIPartsDataStr& AIPartsData) {

				//先頭のイテレータを取得。
				auto itr = AIPartsData.begin();

				//種類を取得。
				std::string type = *(*itr).begin();
				(*itr).erase((*itr).begin());

				//名前を取得。
				std::string name = *(*itr).begin();
				(*itr).erase((*itr).begin());

				//子ノードの数を取得。
				int cNodeNum = std::stoi(*(*itr).begin());
				(*itr).erase((*itr).begin());

				//AI部品の雛形を生成。
				CAIPart* aiPart = nullptr;

				//AI部品を構築。
				{
					if (type == "Sequence") {

						//シーケンスを生成。
						aiPart = new CAISequence;

						//デコレーターを追加。
						CAIDecoratorBuilder m_decoratorBuilder;

						if ((*itr).size() > 0) {

							for (const auto& decoratorStr : (*itr)) {

								aiPart->AddDecorator(m_decoratorBuilder.CreateDecorator(decoratorStr, &m_blackboard));
							}
						}
					}
					else if (type == "Selector") {

						//セレクターを生成。
						aiPart = new CAISelector;

						//デコレーターを追加。
						CAIDecoratorBuilder m_decoratorBuilder;

						if ((*itr).size() > 0) {

							for (const auto& decoratorStr : (*itr)) {

								aiPart->AddDecorator(m_decoratorBuilder.CreateDecorator(decoratorStr, &m_blackboard));
							}
						}
					}
					else if (type == "Task") {

						//タスクを生成。
						CAITaskBuilder AITaskBuilder;
						aiPart = AITaskBuilder.GetAITask(name);
					}
					else {

						//見つからなかった。
						std::string errorMsg = "指定のAI部品が見つかりませんでした。 : ";
						errorMsg += type;

						//警告ウィンドウを出力。
						nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					}

					//名前を設定。
					aiPart->SetName(name);

					//情報を設定。
					aiPart->SetPartInfo(*itr);

					//AIコントローラーを設定。
					aiPart->SetAIController(this);
				}

				//先頭要素を削除。
				AIPartsData.erase(itr);

				//子ノードの数だけAI部品を生成。
				for (int carentNodeNum = 0; carentNodeNum < cNodeNum; carentNodeNum++) {

					//このAI部品の子に生成したAI部品を追加。
					aiPart->AddAIPart(CreateAIPart(AIPartsData));
				}

				//自身をリターン。
				return aiPart;
			}

			void CMonsterAIController::Update(float deltaTime) {

				//クールタイム中なら。
				if (m_isCoolTime) {

					//早期リターン。
					return;
				}

				//デルタタイムを更新。
				m_deltaTimeRef = deltaTime;

				//回転情報を更新。
				UpdateForwardDirection();

				//待機タスクが実行中なら。
				if (m_waitNode != nullptr) {

					//待機タスクだけを実行。
					bool isOk = m_waitNode->Execute(m_blackboard, m_waitNode->GetPartInfo());

					//待機終了したら。
					if (isOk) {

						//初期化。
						m_waitNode = nullptr;
					}
				}
				else {

					//ルートノードからビヘイビアツリーを実行。
					m_rootNode->Execute(m_blackboard, m_rootNode->GetPartInfo());
				}
			}

			void CMonsterAIController::SetPosition(const CVector3& position) {

				//座標を設定。
				m_owner->SetPosition(position);
			}

			const CVector3& CMonsterAIController::GetPosition()const {

				//座標を取得。
				return m_owner->GetPosition();
			}

			void CMonsterAIController::SetRotation(const CQuaternion& rotation) {

				//回転を設定。
				m_owner->SetRotation(rotation);
			}

			const CQuaternion& CMonsterAIController::GetRotation()const {

				//回転を取得。
				return m_owner->GetRotation();
			}

			const CVector3& CMonsterAIController::GetForwardDirection()const {

				//前方向を取得。
				return m_owner->GetForwardDirection();
			}

			void CMonsterAIController::UpdateForwardDirection() {

				//回転行列を計算。
				auto mRot = CMatrix::Identity();
				mRot.MakeRotationFromQuaternion(m_owner->GetRotation());

				//前方向を取得。
				CVector3 forwardDirection = m_owner->GetForwardDirection();

				//前方向を設定。
				forwardDirection.x = mRot.m_fMat[2][0];
				forwardDirection.y = mRot.m_fMat[2][1];
				forwardDirection.z = mRot.m_fMat[2][2];

				//正規化。
				forwardDirection.Normalize();

				//前方向を設定。
				m_owner->SetForwardDirection(forwardDirection);
			}

			void CMonsterAIController::SetState(const EnMonsterState& state) {

				//ステートを設定。
				m_owner->SetState(state);
			}

			const EnMonsterState& CMonsterAIController::GetState()const {

				//ステートを取得。
				return m_owner->GetState();
			}
		}
	}
}