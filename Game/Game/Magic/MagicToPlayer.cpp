#include "YonemaEnginePreCompile.h"
#include "MagicToPlayer.h"


namespace nsAWA {

	namespace nsMagic {

		bool CMagicToPlayer::Start() {

			//エフェクトを生成。
			m_effect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += GetMagicName();
			mainEffectFilePath += ".efkefc";

			//初期化。
			m_effect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//エフェクトの座標を設定。
			m_effect->SetPosition(GetPosition());

			//変更を反映。
			m_effect->Update(0.0f);

			//エフェクトを再生。
			m_effect->Play();

			//自身に効果を付与。
			ExecuteFeature(GetOwner());

			//自身を破棄。
			DeleteGO(this);

			//成功。
			return true;
		}

		void CMagicToPlayer::OnDestroy() {

			//エフェクトを破棄。
			if (m_effect != nullptr) {

				//破棄。
				DeleteGO(m_effect);
				m_effect = nullptr;
			}
		}
	}
}