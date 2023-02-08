#include "YonemaEnginePreCompile.h"
#include "MagicToPlayer.h"


namespace nsAWA {

	namespace nsMagic {

		bool CMagicToPlayer::Start() {

			//�G�t�F�N�g�𐶐��B
			m_effect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += GetMagicName();
			mainEffectFilePath += ".efkefc";

			//�������B
			m_effect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//�G�t�F�N�g�̍��W��ݒ�B
			m_effect->SetPosition(GetPosition());

			//�ύX�𔽉f�B
			m_effect->Update(0.0f);

			//�G�t�F�N�g���Đ��B
			m_effect->Play();

			//���g�Ɍ��ʂ�t�^�B
			ExecuteFeature(GetOwner());

			//���g��j���B
			DeleteGO(this);

			//�����B
			return true;
		}

		void CMagicToPlayer::OnDestroy() {

			//�G�t�F�N�g��j���B
			if (m_effect != nullptr) {

				//�j���B
				DeleteGO(m_effect);
				m_effect = nullptr;
			}
		}
	}
}