#include "YonemaEnginePreCompile.h"
#include "MagicToPlayer.h"


namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr float kEffectDutationTime = 1.0f;	//�G�t�F�N�g�̎�������
			constexpr float kEffectAddPosY = 8.0f;	//�G�t�F�N�g�̉��Z���W
		}

		bool CMagicToPlayer::Start() {

			//�G�t�F�N�g�𐶐��B
			m_effect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += GetMagicName();
			mainEffectFilePath += ".efkefc";

			//�G�t�F�N�g�̎������Ԃ�ݒ�B
			m_effectDurationTime = kEffectDutationTime;

			//�������B
			m_effect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			CVector3 effectPosition = GetPosition();
			effectPosition.y += kEffectAddPosY;

			//�G�t�F�N�g�̍��W��ݒ�B
			m_effect->SetPosition(effectPosition);

			//�ύX�𔽉f�B
			m_effect->Update(0.0f);

			//�G�t�F�N�g���Đ��B
			m_effect->Play();

			//���g�Ɍ��ʂ�t�^�B
			ExecuteFeature(GetOwner());

			//�����B
			return true;
		}

		void CMagicToPlayer::OnDestroy() {

			//�G�t�F�N�g��j���B
			if (m_effect != nullptr) {

				//�j���B
				m_effect->Stop();
				DeleteGO(m_effect);
				m_effect = nullptr;
			}
		}

		void CMagicToPlayer::Update(float deltaTime) {

			//�������Ԃ��X�V�B
			m_effectDurationTime -= deltaTime;

			//�������Ԃ��Ȃ��Ȃ�����B
			if (m_effectDurationTime < 0.0f) {

				//���g��j���B
				DeleteGO(this);
			}
		}
	}
}