#include "YonemaEnginePreCompile.h"
#include "AITaskMove.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskMove::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//移動速度を取得。
				float moveSpeed = std::stof(partInfo[0]);

				//成功距離が指定されているなら取得。
				float successDistance = -1.0f;
				if (partInfo.size() > 1) {

					successDistance = std::stof(partInfo[1]);
				}

				//移動方向を取得。
				CVector3 moveDirection = blackboard.m_targetPosition - m_AIController->GetPosition();

				//正規化。
				CVector3 moveDirectionNormal = moveDirection;
				moveDirectionNormal.Normalize();

				//移動量を計算。
				CVector3 moveAmount = moveDirectionNormal * moveSpeed * m_AIController->GetDeltaTimeRef();

				//移動。
				m_AIController->SetPosition(m_AIController->GetPosition() + moveAmount);

				//ステートを設定。
				m_AIController->SetState(EnMonsterState::enWalk);

				//目的地にたどり着いたら。
				if (moveDirection.Length() < successDistance) {

					//終了。
					return false;
				}

				//成功。
				return true;
			}
		}
	}
}