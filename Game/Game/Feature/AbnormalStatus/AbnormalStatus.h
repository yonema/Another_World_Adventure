#pragma once
#include "../Feature.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			//状態異常の種類
			enum class EnAbnormalStatusType {

				enPoison,	//毒

				enNum,		//状態異常の数
				enNone		//設定なし
			};

			//状態異常クラス
			class CAbnormalStatus : public CFeature
			{
			public:
				void Create()override final;

				CFeature* CreateAndReturn()override final;

				void Init(
					EnAbnormalStatusType abnormalStatusType,
					IGameActor* target,
					int abnormalStatusLevel
				);
			protected:
				virtual void Init() {}

				void Execute(float deltaTime)override {}

			private:
				EnAbnormalStatusType m_type = EnAbnormalStatusType::enNone;	//状態異常の種類
				int m_abnormalStatusLevel = 0;			//状態異常レベル
			protected:
				IGameActor* m_target = nullptr;			//ターゲット
			};
		}
	}
}