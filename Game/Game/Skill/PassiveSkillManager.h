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
			void Init();

			void SetPassiveSkill(int skillNum, nsSkill::CPassiveSkill* passiveSkill);

			void AddPassiveSkillSize() {

				//装着可能な数を加算。
				m_passiveSkillMaxNum++;
			}

			void UpdatePassiveSkill();

			const std::vector<nsSkill::CPassiveSkill*>& GetPassiveSkillList()const {

				//パッシブスキルのリストを取得。
				return m_passiveSkill;
			}

			int GetPassiveSkillMaxNum()const {

				//パッシブスキルの最大可能装着数をリターン。
				return m_passiveSkillMaxNum;
			}

		private:
			int m_passiveSkillMaxNum = 5;						//パッシブスキルの最大可能装着数
			std::vector<nsSkill::CPassiveSkill*> m_passiveSkill;	//パッシブスキル
		};
	}
}

