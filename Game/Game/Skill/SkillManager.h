#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsSkill {

		//�X�L���Ǘ��N���X
		class CSkillManager : nsUtils::SNoncopyable
		{
		public:
			void FindPlayer();

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//�v���C���[�̃|�C���^
		};
	}
}