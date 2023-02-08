#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			//バフかデバフか
			enum class EnBuffOrDebuff {

				enBuff,		//バフ
				enDebuff,	//デバフ

				enNone		//設定なし
			};

			//バフ・デバフクラス
			class CBuffDebuff : public CFeature
			{
			public:
				void Init(const std::string& buffOrDebuff,
					const std::string& statusRef,
					float value,
					float durationTime
				);

				void Create()override final;

				float Apply(EnStatusRef statusRef) {

					//一致するなら。
					if (m_statusRef == statusRef) {

						//固有の値を返す。
						return m_value;
					}
					//一致していないなら
					else {
						//変化なし。
						return 0.0f;
					}
				}

			private:
				EnBuffOrDebuff GetBuffOrDebuff(const std::string& buffOrDebuff)const;

				EnStatusRef GetStatusRef(const std::string& statusRef)const;

			private:
				EnBuffOrDebuff m_buffOrDebuff = EnBuffOrDebuff::enNone;		//バフかデバフか
				EnStatusRef m_statusRef = EnStatusRef::enNone;				//参照ステータス
				float m_value = 0.0f;		//増減値
			};
		}
	}
}
