#pragma once
#include "../StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		//状態異常の種類
		enum class EnAbnormalStatusType {

			enPoison,	//毒

			enNum,		//状態異常の数
			enNone		//設定なし
		};

		//状態異常クラス
		class CAbnormalStatus : public CStatusChanger
		{
			//状態異常生成クラスはフレンド
			friend class CAbnormalStatusBuilder;

		protected:
			virtual void Init() {}

			void ExecuteAtStart(float deltaTime)override{}

		private:
			EnAbnormalStatusType m_type = EnAbnormalStatusType::enNone;	//状態異常の種類
		};

		//状態異常生成クラス
		class CAbnormalStatusBuilder : public CFeature {

		public:
			void Init(
				EnAbnormalStatusType abnormalStatusType,
				IGameActor* target,
				int abnormalStatusLevel
			);

			void Create()override final;
		private:
			EnAbnormalStatusType m_abnormalStatusType = EnAbnormalStatusType::enNone;	//状態異常の種類
			IGameActor* m_target = nullptr;			//ターゲット
			int m_abnormalStatusLevel = 0;			//状態異常レベル
		};
	}
}