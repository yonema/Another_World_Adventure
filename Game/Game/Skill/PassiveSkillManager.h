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

			void Release();

			void SetPassiveSkill(int skillNum, nsSkill::CPassiveSkill* passiveSkill);

			nsSkill::CPassiveSkill* GetPassiveSkill(int skillNum)const{
			
				//番号が範囲外なら。
				if (skillNum >= m_passiveSkillMaxNum) {

					//エラー出力。
					nsGameWindow::MessageBoxError(L"CPassiveSKill : 設定範囲外の番号です。");
					std::abort();
				}

				//パッシブスキルをリターン。
				return m_passiveSkill[skillNum];
			}

			void SetPassiveSkillMaxNum(int maxNum) {

				//装着可能な数を設定。
				m_passiveSkillMaxNum = maxNum;

				//枠のサイズを変更。
				m_passiveSkill.resize(m_passiveSkillMaxNum);
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

