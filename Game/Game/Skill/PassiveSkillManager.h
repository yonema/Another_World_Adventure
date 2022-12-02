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
			void AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill);

			void UpdatePassiveSkill();
		private:
			int m_passiveSkillMaxNum = 5;						//�p�b�V�u�X�L���̍ő�\������
			std::list<nsSkill::CPassiveSkill*> m_passiveSkill;	//�p�b�V�u�X�L��
		};
	}
}

