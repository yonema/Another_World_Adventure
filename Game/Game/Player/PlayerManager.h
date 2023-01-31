#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayer;

		//プレイヤー管理クラス
		class CPlayerManager : nsUtils::SNoncopyable
		{
		public:
			bool FindPlayer();

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

			void SetWeapon(const std::string& weaponName);

			void SetArmor(const std::string& armorName);

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//プレイヤーのポインタ
		};
	}
}