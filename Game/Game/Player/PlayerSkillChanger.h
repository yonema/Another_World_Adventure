#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsSkill {

		class CActiveSkill;
	}

	namespace nsPlayer {
		
		class CPlayerAction;
	}

	namespace nsPlayer {

		//プレイヤーのスキル変更クラス
		class CPlayerSkillChanger : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void SetActiveSkill(int skillNum, const std::string& skillName);

			nsSkill::CActiveSkill* CreateActiveSkill(const std::string skillName);

		private:
			CPlayerAction* m_playerAction = nullptr;	//プレイヤーのアクションクラス
		};
	}
}