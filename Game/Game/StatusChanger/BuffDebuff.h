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
		class CBuffDebuffBuilder : public nsUtils::SNoncopyable {

		public:
			void Create(
				EnBuffOrDebuff buffOrDebuff,
				IGameActor* target,
				EnStatusRef statusRef,
				float value,
				float durationTime
			);
		};
	}
}
