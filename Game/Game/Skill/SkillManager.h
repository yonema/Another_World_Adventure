#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsSkill {

		//スキル管理クラス
		class CSkillManager : nsUtils::SNoncopyable
		{
		public:
			void FindPlayer();

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//プレイヤーのポインタ
		};
	}
}