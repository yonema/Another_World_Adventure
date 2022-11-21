#pragma once
#include "StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		//バフかデバフか
		enum class EnBuffOrDebuff {

			enBuff,		//バフ
			enDebuff,	//デバフ

			enNone		//設定なし
		};

		//バフ・デバフクラス
		class CBuffDebuff : public CStatusChanger
		{
			//バフデバフ生成クラスはフレンド
			friend class CBuffDebuffBuilder;
		private:

			void Init();

			//void ExecuteAtStart(float deltaTime)override final;
			//void ExecuteAtEnd(float deltaTime)override final;

		public:

			float Apply(EnStatusRef statusRef) {

				//一致するなら。
				if (m_statusRef == statusRef) {

					//固有の値を返す。
					return m_value;
				}
				//一致していないなら
				else {
					//等倍を返す。
					return 1.0f;
				}
			}
		private:
			EnBuffOrDebuff m_buffOrDebuff = EnBuffOrDebuff::enNone;		//バフかデバフか
			EnStatusRef m_statusRef = EnStatusRef::enNone;				//参照ステータス
			float m_value = 0.0f;		//増減値
		};

		//バフデバフ生成クラス
		class CBuffDebuffBuilder : public CFeature {

		public:
			void Init(EnBuffOrDebuff buffOrDebuff,
				IGameActor* target,
				EnStatusRef statusRef,
				float value,
				float durationTime
			);

			void Create()override final;
		private:
			EnBuffOrDebuff m_buffOrDebuff = EnBuffOrDebuff::enNone;		//バフかデバフか
			IGameActor* m_target = nullptr;								//ターゲット
			EnStatusRef m_statusRef = EnStatusRef::enNone;				//参照ステータス
			float m_value = 0.0f;										//増減値
			float m_durationTime = 0.0f;								//持続時間
		};
	}
}
