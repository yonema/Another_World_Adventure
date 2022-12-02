#pragma once
#include "AbnormalStatus.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			//麻痺クラス
			class CParalysis : public CAbnormalStatus
			{
			public:
				void Init()override final;

				void Execute(float deltaTime)override final;

				bool CanUseActiveSkill()const {

					//アクティブスキルを使用できるかをリターン。
					return m_canUseActiveSkill;
				}
			private:
				bool m_canUseActiveSkill = false;	//アクティブスキルを使用できる？
			};
		}
	}
}

