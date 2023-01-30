#include "YonemaEnginePreCompile.h"
#include "AITaskRotateToTargetPosition.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr const float kRotationSlerpRate = 9.375f;			//回転の補間率
			}

			bool CAITaskRotateToTargetPosition::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//回転の雛形を生成。
				CQuaternion rotation = CQuaternion::Identity();

				//目標と自身の座標から移動方向を求める。
				CVector3 moveDirection = blackboard.m_targetPosition - m_AIController->GetPosition();

				//正規化。
				moveDirection.Normalize();

				//回転角度を求める。
				float angle = atan2(-moveDirection.x, moveDirection.z);

				//回転情報を設定。
				CQuaternion rotSource = CQuaternion::Identity();
				rotSource.SetRotation(CVector3::AxisY(), -angle);

				//補間するかどうかを取得。
				bool slerp = partInfo[0] == "TRUE" ? true : false;

				//補間するかどうか。
				if (slerp) {

					//回転情報を取得。
					rotation = m_AIController->GetRotation();

					//回転速度の補間率を求める。
					float rotationSlerpRate = kRotationSlerpRate * m_AIController->GetDeltaTimeRef();

					//線形補間。
					rotation.Slerp(rotationSlerpRate, rotation, rotSource);
				}
				else {

					//そのまま設定。
					rotation = rotSource;
				}

				//回転を設定。
				m_AIController->SetRotation(rotation);

				//前方向を更新。
				m_AIController->UpdateForwardDirection();

				//成功。
				return true;
			}
		}
	}
}