#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "PassiveSkillManager.h"

namespace nsAWA {

	namespace nsSkill {

		void CPassiveSkillManager::AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill) {

			//�ő�\�������𒴂��ĂȂ��Ȃ�B
			if (m_passiveSkill.size() < m_passiveSkillMaxNum) {

				//�p�b�V�u�X�L���𑕒�����B
				m_passiveSkill.emplace_back(passiveSkill);
			}
		}

		void CPassiveSkillManager::UpdatePassiveSkill() {

			//�p�b�V�u�X�L�������ɎQ�ƁB
			for (const auto& passiveSkill : m_passiveSkill) {

				//�X�V�B
				passiveSkill->Update();
			}
		}
	}
}