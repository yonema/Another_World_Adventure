#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;
	};

	//���[�U�[�f�[�^�Ǘ��N���X
	class CUserData : nsUtils::SNoncopyable
	{
	public:
		void Save();

		void Load();

	private:
		void SaveStatus(nsPlayer::CPlayer* player);

		void SaveCanUseActiveSkillList(nsPlayer::CPlayer* player);

		void SaveItem();

		void SaveWeaponAndArmor(nsPlayer::CPlayer* player);

		void SaveSetActiveSkill(nsPlayer::CPlayer* player);

		void SaveSetPassiveSkill(nsPlayer::CPlayer* player);

	private:
		std::list<std::vector<std::string>> m_userData;		//���[�U�[�f�[�^
	};
}