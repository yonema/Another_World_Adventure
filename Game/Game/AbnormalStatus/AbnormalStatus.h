#pragma once
#include "../GameActor.h"

namespace nsAWA {

	namespace nsAbnormalStatus {

		//状態異常の種類
		enum EnAbnormalStatusType {

			enPoison,	//毒

			enNum,		//状態異常の数
			enNone		//設定なし
		};

		//状態異常クラス
		class CAbnormalStatus : nsUtils::SNoncopyable
		{
			//状態異常生成クラスはフレンド
			friend class CAbnormalStatusBuilder;
		public:
			bool Update(float deltaTime);

		protected:
			virtual void Init() {}

			virtual void Execute(float deltaTime) = 0;

		protected:
			IGameActor* m_target = nullptr;		//効果をもたらすターゲット

		private:
			float m_durationTimer = 0.0f;		//持続時間
			EnAbnormalStatusType m_type = EnAbnormalStatusType::enNone;	//状態異常の種類
		};

		//状態異常生成クラス
		class CAbnormalStatusBuilder : nsUtils::SNoncopyable {

		public:
			void Create(
				EnAbnormalStatusType abnormalStatusType,
				IGameActor* target,
				int abnormalStatusLevel
			);
		};
	}
}