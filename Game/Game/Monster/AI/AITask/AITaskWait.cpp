#include "YonemaEnginePreCompile.h"
#include "AITaskWait.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskWait::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				if (m_AIController->GetState() == EnMonsterState::enIdle) {

					//�^�C�}�[���X�V�B
					blackboard.m_waitTimer -= m_AIController->GetDeltaTimeRef();

					//�^�C�}�[��0�ɂȂ�����B
					if (blackboard.m_waitTimer <= 0.0f) {

						//�ҋ@���I������̂Ő����B
						return true;
					}
					else {

						//�܂��ҋ@���B
						return false;
					}
				}
				else {

					//AI�R���g���[���[�ɂ��̑ҋ@�^�X�N��ݒ�B
					m_AIController->SetWaitNode(this);

					//�X�e�[�g��ҋ@��Ԃɐݒ�B
					m_AIController->SetState(EnMonsterState::enIdle);

					//�ҋ@���Ԃ��擾�B
					float waitTime = std::stof(partInfo[0]);

					//�ҋ@���Ԃ�ݒ�B
					blackboard.m_waitTimer = waitTime;

					//�ҋ@���Ă��āA����ȏ�i�߂����Ȃ��̂Ŏ��s�Ƃ���B
					return false;
				}
			}
		}
	}
}