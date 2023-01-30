#include "YonemaEnginePreCompile.h"
#include "AITaskIsButtle.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr float kDistanceforButtle = 80.0f;		//�o�g���𑱂��邽�߂̋���
			}

			bool CAITaskIsButtle::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�^�[�Q�b�g�Ƃ̋������v�Z�B
				CVector3 distanceToTarget = blackboard.m_targetPosition - m_AIController->GetPosition();

				//��苗���ȓ��Ȃ�B
				if (distanceToTarget.Length() <= kDistanceforButtle) {

					//�����B
					return true;
				}
				else {

					//���s�B
					return false;
				}
			}
		}
	}
}