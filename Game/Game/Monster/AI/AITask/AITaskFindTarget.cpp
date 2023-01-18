#include "YonemaEnginePreCompile.h"
#include "AITaskFindTarget.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskFindTarget::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//視野角を取得。
				float fieldOfView = std::stof(partInfo[0]);

				//有効距離を取得。
				float distance = std::stof(partInfo[1]);

				//ターゲットに向かうベクトルを求める。
				CVector3 vecToTargetPosition = blackboard.m_targetPosition - m_AIController->GetPosition();

				//ターゲットとの距離が設定より長かったら。
				if (vecToTargetPosition.Length() > distance) {

					//見つけられないので失敗。
					return false;
				}

				//正規化。
				vecToTargetPosition.Normalize();

				//自身の前方向を取得。
				CVector3 forwardDirection = m_AIController->GetForwardDirection();

				//正規化。
				forwardDirection.Normalize();

				//内積からターゲットとの角度を計算。
				float resultFieldOfView = nsMath::RadToDeg(std::acos(nsMath::Dot(vecToTargetPosition, forwardDirection)));

				//視野に入っているか計算。
				if (resultFieldOfView <= fieldOfView) {

					//見つけたので成功。
					return true;
				}

				//失敗。
				return false;
			}
		}
	}
}