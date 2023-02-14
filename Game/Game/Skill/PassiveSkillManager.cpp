#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "PassiveSkillManager.h"

namespace nsAWA {

	namespace nsSkill {

		void CPassiveSkillManager::Init() {


		}

		void CPassiveSkillManager::Release() {

			//�p�b�V�u�X�L����j���B
			for (auto itr = m_passiveSkill.begin(); itr != m_passiveSkill.end(); ) {

				if ((*itr) != nullptr) {
					//�j���B
					delete (*itr);
				}
				itr = m_passiveSkill.erase(itr);

				continue;
			}
		}

		void CPassiveSkillManager::SetPassiveSkill(int skillNum, nsSkill::CPassiveSkill* passiveSkill) {

			//�ő�\�������𒴂��Ă���Ȃ�B
			if (m_passiveSkillMaxNum <= skillNum) {

				nsGameWindow::MessageBoxError(L"CPassiveSkillManager : �T�C�Y�𒴂��ăp�b�V�u�X�L���𑕒����悤�Ƃ��Ă��܂��B");
			}
			else {

				//���ɓo�^����Ă���Ȃ�B
				if (m_passiveSkill[skillNum] != nullptr) {

					//�j���B
					m_passiveSkill[skillNum]->ReleaseFeature();
					delete m_passiveSkill[skillNum];
				}

				//�V���ȃp�b�V�u�X�L����ݒ�B
				m_passiveSkill[skillNum] = passiveSkill;
			}
		}

		void CPassiveSkillManager::UpdatePassiveSkill() {

			for (const auto& passiveSkill : m_passiveSkill) {

				//�p�b�V�u�X�L�����o�^����Ă��Ȃ�������B
				if (passiveSkill == nullptr) {

					//���ցB
					continue;
				}

				//�X�V�B
				passiveSkill->Update();
			}
		}
	}
}