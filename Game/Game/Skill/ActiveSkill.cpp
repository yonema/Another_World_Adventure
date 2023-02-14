#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"

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
	}
}