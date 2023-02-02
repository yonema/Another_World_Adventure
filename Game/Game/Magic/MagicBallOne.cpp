#include "YonemaEnginePreCompile.h"
#include "MagicBallOne.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr float kTriggerRadius = 2.0f;	//トリガーの半径
			constexpr float kDurationTime = 1.0f;	//持続時間
			constexpr float kMoveAmount = 50.0f;	//移動量
			constexpr float kAddPositionY = 10.0f;	//調整用加算座標
		}

		bool CMagicBallOne::Start() {

			//座標を調整。
			m_position.y += kAddPositionY;

			//当たり判定を初期化。
			m_trigger.InitAsSphere(kTriggerRadius, m_position);

			//メインエフェクトを生成。
			m_mainEffect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += m_name;
			mainEffectFilePath += "_Main.efk";

			//初期化。
			m_mainEffect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//エフェクトの座標を設定。
			m_mainEffect->SetPosition(m_position);

			//エフェクトを再生。
			m_mainEffect->Play();

			//持続時間を設定。
			m_durationTime = kDurationTime;

			//成功。
			return true;
		}

		void CMagicBallOne::OnDestroy() {

			//エフェクトを破棄。
			DeleteGO(m_mainEffect);
			m_mainEffect = nullptr;

			DeleteGO(m_endEffect);
			m_endEffect = nullptr;

			//当たり判定を破棄。
			m_trigger.Release();
		}

		void CMagicBallOne::Update(float deltaTime) {

			//持続時間を更新。
			m_durationTime -= deltaTime;

			//持続時間が無くなったら
			if (m_durationTime < 0.0f) {

				//自身を破棄。
				DeleteGO(this);
			}

			//座標を更新。
			m_position += m_moveDirection * kMoveAmount * deltaTime;
			m_mainEffect->SetPosition(m_position);
			m_trigger.SetPosition(m_position);
		}
	}
}