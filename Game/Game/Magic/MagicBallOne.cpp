#include "YonemaEnginePreCompile.h"
#include "MagicBallOne.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr float kTriggerRadius = 2.0f;	//�g���K�[�̔��a
			constexpr float kDurationTime = 1.0f;	//��������
			constexpr float kMoveAmount = 50.0f;	//�ړ���
			constexpr float kAddPositionY = 10.0f;	//�����p���Z���W
		}

		bool CMagicBallOne::Start() {

			//���W�𒲐��B
			m_position.y += kAddPositionY;

			//�����蔻����������B
			m_trigger.InitAsSphere(kTriggerRadius, m_position);

			//���C���G�t�F�N�g�𐶐��B
			m_mainEffect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += m_name;
			mainEffectFilePath += "_Main.efk";

			//�������B
			m_mainEffect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//�G�t�F�N�g�̍��W��ݒ�B
			m_mainEffect->SetPosition(m_position);

			//�G�t�F�N�g���Đ��B
			m_mainEffect->Play();

			//�������Ԃ�ݒ�B
			m_durationTime = kDurationTime;

			//�����B
			return true;
		}

		void CMagicBallOne::OnDestroy() {

			//�G�t�F�N�g��j���B
			DeleteGO(m_mainEffect);
			m_mainEffect = nullptr;

			DeleteGO(m_endEffect);
			m_endEffect = nullptr;

			//�����蔻���j���B
			m_trigger.Release();
		}

		void CMagicBallOne::Update(float deltaTime) {

			//�������Ԃ��X�V�B
			m_durationTime -= deltaTime;

			//�������Ԃ������Ȃ�����
			if (m_durationTime < 0.0f) {

				//���g��j���B
				DeleteGO(this);
			}

			//���W���X�V�B
			m_position += m_moveDirection * kMoveAmount * deltaTime;
			m_mainEffect->SetPosition(m_position);
			m_trigger.SetPosition(m_position);
		}
	}
}