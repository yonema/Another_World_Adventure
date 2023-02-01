#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//アクティブスキル
		class CActiveSkill : public CSkill
		{
		public:
			//アクティブスキルのタイプ
			enum class EnActiveSkillType {

				enSword,	//剣スキル
				enAxe,		//斧スキル
				enWand,		//杖スキル
				enMagic,	//魔法スキル
				enNum,		//タイプ数

				enNone = -1//設定なし
			};
		public:
			void SetUseMP(float useMP) {

				//消費MPを設定。
				m_useMP = useMP;
			}

			void SetType(EnActiveSkillType type) {

				//タイプの設定がおかしいなら。
				if (type == EnActiveSkillType::enNone || type > EnActiveSkillType::enNum) {
#ifdef _DEBUG
					//エラー出力。
					nsGameWindow::MessageBoxError(L"アクティブスキルのタイプ設定が不適切です。");
#endif // _DEBUG
					std::abort();
				}

				//タイプを設定。
				m_activeSkillType = type;
			}

			EnActiveSkillType GetType()const {

				//タイプを取得。
				return m_activeSkillType;
			}

			float GetUseMP()const {

				//消費MPをリターン。
				return m_useMP;
			}
		public:
			static const int m_kActiveSkillNumMax;
		private:
			float m_useMP = 0.0f;	//消費MP
			EnActiveSkillType m_activeSkillType = EnActiveSkillType::enNone;	//アクティブスキルのタイプ
		};
	}
}

