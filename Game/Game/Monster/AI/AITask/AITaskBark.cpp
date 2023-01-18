#include "YonemaEnginePreCompile.h"
#include "AITaskBark.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskBark::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�X�e�[�g��ݒ�B
				m_AIController->SetState(EnMonsterState::enBark);

				//�N�[���^�C����ON�ɐݒ�B
				m_AIController->CoolTimeOn();

				//�����B
				return true;
			}
		}
	}
}