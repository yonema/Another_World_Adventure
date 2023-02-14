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

			using ActiveSkillAnimEventData = std::list<std::vector<std::string>>;

			struct SActiveSkillAnimData {

				std::string skillName = "NoName";			//�X�L���̖��O
				std::string index = "NoIndex";				//�A�j���[�V�����C�x���g�ɃC���f�b�N�X
				ActiveSkillAnimEventData sAnimEventData;	//�A�j���[�V�����C�x���g�f�[�^
			};
		public:
			void Execute();

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

			void SetAnimaitonFilePath(const std::string& animFilePath) {

				//�A�j���[�V�����̃t�@�C���p�X��ݒ�B
				m_animFilePath = animFilePath;
			}

			const std::string& GetAnimationFilePath()const {

				//�A�j���[�V�����̃t�@�C���p�X�����^�[���B
				return m_animFilePath;
			}

			void SetAnimDataList(const std::list<SActiveSkillAnimData>& animDataList) {

				//�A�j���[�V�����f�[�^�̃��X�g��ݒ�B
				m_activeSkillAnimDataList = animDataList;
			}

			void SetEffectName(const std::string& effectName) {
				
				//�G�t�F�N�g�̖��O��ݒ�B
				m_effectName = effectName;
			}

			const SActiveSkillAnimData& GetActiveSkillAnimData(const std::string& index)const;
		public:
			static int m_kActiveSkillNumMax;
		private:
			float m_useMP = 0.0f;	//����MP
			std::string m_animFilePath = "NoFilePath";							//�A�j���[�V�����̃t�@�C���p�X
			EnActiveSkillType m_activeSkillType = EnActiveSkillType::enNone;	//�A�N�e�B�u�X�L���̃^�C�v
			std::string m_effectName = "NoName";						//�G�t�F�N�g�̖��O
			std::list<SActiveSkillAnimData> m_activeSkillAnimDataList;	//�A�N�e�B�u�X�L���̃A�j���[�V�����f�[�^�̃��X�g
		};
	}
}

