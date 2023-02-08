#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr float kPassiveSkillDurationTime = 999.9f;	//�p�b�V�u�X�L�����̌��ʂ̎�������
		}

		void CPassiveSkill::ReleaseFeature() {

			//���ʂ����ɎQ�ƁB
			for (const auto& feature : m_featureList) {

				//���ʂ�j���B
				feature->End();
			}
		}

		void CPassiveSkill::Update() {

			//���ʂ����ɎQ�ƁB
			for (const auto& feature : m_featureList) {

				//���ʂ̎������Ԃ��X�V�B
				feature->SetDurationTime(kPassiveSkillDurationTime);
			}
		}
	}
}