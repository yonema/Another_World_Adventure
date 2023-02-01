#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//�A�N�e�B�u�X�L��
		class CActiveSkill : public CSkill
		{
		public:
			//�A�N�e�B�u�X�L���̃^�C�v
			enum class EnActiveSkillType {

				enSword,	//���X�L��
				enAxe,		//���X�L��
				enWand,		//��X�L��
				enMagic,	//���@�X�L��
				enNum,		//�^�C�v��

				enNone = -1//�ݒ�Ȃ�
			};
		public:
			void SetUseMP(float useMP) {

				//����MP��ݒ�B
				m_useMP = useMP;
			}

			void SetType(EnActiveSkillType type) {

				//�^�C�v�̐ݒ肪���������Ȃ�B
				if (type == EnActiveSkillType::enNone || type > EnActiveSkillType::enNum) {
#ifdef _DEBUG
					//�G���[�o�́B
					nsGameWindow::MessageBoxError(L"�A�N�e�B�u�X�L���̃^�C�v�ݒ肪�s�K�؂ł��B");
#endif // _DEBUG
					std::abort();
				}

				//�^�C�v��ݒ�B
				m_activeSkillType = type;
			}

			EnActiveSkillType GetType()const {

				//�^�C�v���擾�B
				return m_activeSkillType;
			}

			float GetUseMP()const {

				//����MP�����^�[���B
				return m_useMP;
			}
		public:
			static const int m_kActiveSkillNumMax;
		private:
			float m_useMP = 0.0f;	//����MP
			EnActiveSkillType m_activeSkillType = EnActiveSkillType::enNone;	//�A�N�e�B�u�X�L���̃^�C�v
		};
	}
}

