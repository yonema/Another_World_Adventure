#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsSkill {

		class CPassiveSkill;
	}

	namespace nsSkill {

		//�p�b�V�u�X�L���Ǘ��N���X
		class CPassiveSkillManager : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void Release();

			void SetPassiveSkill(int skillNum, nsSkill::CPassiveSkill* passiveSkill);

			nsSkill::CPassiveSkill* GetPassiveSkill(int skillNum)const{
			
				//�ԍ����͈͊O�Ȃ�B
				if (skillNum >= m_passiveSkillMaxNum) {

					//�G���[�o�́B
					nsGameWindow::MessageBoxError(L"CPassiveSKill : �ݒ�͈͊O�̔ԍ��ł��B");
					std::abort();
				}

				//�p�b�V�u�X�L�������^�[���B
				return m_passiveSkill[skillNum];
			}

			void SetPassiveSkillMaxNum(int maxNum) {

				//�����\�Ȑ���ݒ�B
				m_passiveSkillMaxNum = maxNum;

				//�g�̃T�C�Y��ύX�B
				m_passiveSkill.resize(m_passiveSkillMaxNum);
			}

			void UpdatePassiveSkill();

			const std::vector<nsSkill::CPassiveSkill*>& GetPassiveSkillList()const {

				//�p�b�V�u�X�L���̃��X�g���擾�B
				return m_passiveSkill;
			}

			int GetPassiveSkillMaxNum()const {

				//�p�b�V�u�X�L���̍ő�\�����������^�[���B
				return m_passiveSkillMaxNum;
			}

		private:
			int m_passiveSkillMaxNum = 5;						//�p�b�V�u�X�L���̍ő�\������
			std::vector<nsSkill::CPassiveSkill*> m_passiveSkill;	//�p�b�V�u�X�L��
		};
	}
}

