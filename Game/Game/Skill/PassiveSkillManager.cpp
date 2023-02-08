#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "PassiveSkillManager.h"

namespace nsAWA {

	namespace nsSkill {

		void CPassiveSkillManager::Init() {

			//�g�̃T�C�Y���������B
			m_passiveSkill.resize(m_passiveSkillMaxNum);
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
					delete m_passiveSkill[skillNum];
				}

				//�V�����p�b�V�u�X�L���𑕒�����B
				//m_passiveSkill[skillNum] = new nsSkill::CPassiveSkill;
				//m_passiveSkill[skillNum]->SetFeatureList(passiveSkill->GetFeatureList());
				//m_passiveSkill[skillNum]->SetName(passiveSkill->GetName());

				//delete passiveSkill;
				m_passiveSkill[skillNum] = passiveSkill;
			}
		}

		void CPassiveSkillManager::UpdatePassiveSkill() {

			//�p�b�V�u�X�L�������ɎQ�ƁB
			//for (int skillNum = 0; skillNum < m_passiveSkill.size(); skillNum++) {
			//
			//	//�p�b�V�u�X�L�����ݒ肳��Ă��Ȃ�������B
			//	if (m_passiveSkill[skillNum] == nullptr) {
			//
			//		//�I���B
			//		return;
			//	}
			//
			//	//�X�V�B
			//	m_passiveSkill[skillNum]->Update();
			//}

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