#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsSkill {

		class CActiveSkill;
	}

	namespace nsPlayer {
		
		class CPlayerAction;
	}

	namespace nsPlayer {

		//�v���C���[�̃X�L���ύX�N���X
		class CPlayerSkillChanger : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void SetActiveSkill(int skillNum, const std::string& skillName);

			nsSkill::CActiveSkill* CreateActiveSkill(const std::string skillName);

		private:
			CPlayerAction* m_playerAction = nullptr;	//�v���C���[�̃A�N�V�����N���X
		};
	}
}