#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsSkill {

		class CPassiveSkill;
	}

	namespace nsSkill {

		//パッシブスキル管理クラス
		class CPassiveSkillManager : nsUtils::SNoncopyable
		{
		public:
			void AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill);

			void UpdatePassiveSkill();
		private:
			int m_passiveSkillMaxNum = 5;						//パッシブスキルの最大可能装着数
			std::list<nsSkill::CPassiveSkill*> m_passiveSkill;	//パッシブスキル
		};
	}
}

