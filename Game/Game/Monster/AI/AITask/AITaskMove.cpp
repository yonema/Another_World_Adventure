#include "YonemaEnginePreCompile.h"
#include "AITaskMove.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskMove::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�ړ����x���擾�B
				float moveSpeed = std::stof(partInfo[0]);

				//�����������w�肳��Ă���Ȃ�擾�B
				float successDistance = -1.0f;
				if (partInfo.size() > 1) {

					successDistance = std::stof(partInfo[1]);
				}

				//�ړ��������擾�B
				CVector3 moveDirection = blackboard.m_targetPosition - m_AIController->GetPosition();

				//���K���B
				CVector3 moveDirectionNormal = moveDirection;
				moveDirectionNormal.Normalize();

				//�ړ��ʂ��v�Z�B
				CVector3 moveAmount = moveDirectionNormal * moveSpeed * m_AIController->GetDeltaTimeRef();

				//�ړ��B
				m_AIController->SetPosition(m_AIController->GetPosition() + moveAmount);

				//�X�e�[�g��ݒ�B
				m_AIController->SetState(EnMonsterState::enWalk);

				//�ړI�n�ɂ��ǂ蒅������B
				if (moveDirection.Length() < successDistance) {

					//�I���B
					return false;
				}

				//�����B
				return true;
			}
		}
	}
}