#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"
#include "../Player/Player.h"

namespace nsAWA {

	namespace nsSkill {

		int CActiveSkill::m_kActiveSkillNumMax = 6;

		const CActiveSkill::SActiveSkillAnimData& CActiveSkill::GetActiveSkillAnimData(const std::string& index)const {

			//�A�N�e�B�u�X�L���̃A�j���[�V�����f�[�^�����ɎQ�ƁB
			for (const auto& animData : m_activeSkillAnimDataList) {

				//�C���f�b�N�X����v������B
				if (animData.index == index) {

					//���̃A�j���[�V�����f�[�^�����^�[���B
					return animData;
				}
			}
			
#ifdef _DEBUG
			//�G���[�o�́B
			nsGameWindow::MessageBoxError(L"CActiveSkill : �X�L���̃A�j���[�V�����f�[�^��������܂���ł����B");
			std::abort();
#endif // _DEBUG
		}

		void CActiveSkill::Execute() {

			if (m_effectName != "NoName") {

				//�v���C���[�ɕ���Ǘ��N���X���擾�B
				auto playerWeaponManager = dynamic_cast<nsPlayer::CPlayer*>(FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player))->GetWeaponManager();
				
				//�G�t�F�N�g�𐶐��B
				playerWeaponManager->CreateEffect(m_effectName);
			}
		}
	}
}