#include "YonemaEnginePreCompile.h"
#include "MagicToPlayer.h"


namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr float kEffectDutationTime = 1.0f;	//エフェクトの持続時間
			constexpr float kEffectAddPosY = 8.0f;	//エフェクトの加算座標
		}

		bool CMagicToPlayer::Start() {

			//エフェクトを生成。
			m_effect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += GetMagicName();
			mainEffectFilePath += ".efkefc";

			//エフェクトの持続時間を設定。
			m_effectDurationTime = kEffectDutationTime;

			//初期化。
			m_effect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			CVector3 effectPosition = GetPosition();
			effectPosition.y += kEffectAddPosY;

			//エフェクトの座標を設定。
			m_effect->SetPosition(effectPosition);

			//変更を反映。
			m_effect->Update(0.0f);

			//エフェクトを再生。
			m_effect->Play();

			//自身に効果を付与。
			ExecuteFeature(GetOwner());

			//成功。
			return true;
		}

		void CMagicToPlayer::OnDestroy() {

			//エフェクトを破棄。
			if (m_effect != nullptr) {

				//破棄。
				m_effect->Stop();
				DeleteGO(m_effect);
				m_effect = nullptr;
			}
		}

		void CMagicToPlayer::Update(float deltaTime) {

			//持続時間を更新。
			m_effectDurationTime -= deltaTime;

			//持続時間がなくなったら。
			if (m_effectDurationTime < 0.0f) {

				//自身を破棄。
				DeleteGO(this);
			}
		}
	}
}