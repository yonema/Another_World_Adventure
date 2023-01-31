#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;

		//�v���C���[�Ǘ��N���X
		class CPlayerManager : nsUtils::SNoncopyable
		{
		public:
			bool FindPlayer();

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

			void SetWeapon(const std::string& weaponName);

			void SetArmor(const std::string& armorName);

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//�v���C���[�̃|�C���^
		};
	}
}