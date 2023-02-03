#include "YonemaEnginePreCompile.h"
#include "MagicBallOne.h"
#include "../GameActorCollider.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr float kTriggerRadius = 5.0f;	//�g���K�[�̔��a
			constexpr float kDurationTime = 1.0f;	//��������
			constexpr float kMoveAmount = 50.0f;	//�ړ���
			constexpr float kAddPositionY = 10.0f;	//�����p���Z���W
			constexpr float kAddPositionMoveDirection = 10.0f;	//�����p���Z���W
		}

		bool CMagicBallOne::Start() {

			//���W�𒲐��B
			CVector3 position = GetPosition();
			position.y += kAddPositionY;
			position += GetMoveDirection() * kAddPositionMoveDirection;

			//���W��ݒ�B
			SetPosition(position);

			//�����蔻����������B
			m_trigger.InitAsSphere(kTriggerRadius, GetPosition());

			//TriggerEnter�̃R�[���o�b�N�֐���ݒ�B
			m_trigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) {OnTriggerEnter(otherData); });

			//���C���G�t�F�N�g�𐶐��B
			m_mainEffect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += GetMagicName();
			mainEffectFilePath += "_Main.efk";

			//�������B
			m_mainEffect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//�G�t�F�N�g�̍��W��ݒ�B
			m_mainEffect->SetPosition(position);

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

			//�������Ԃ������Ȃ�����B
			if (m_durationTime < 0.0f) {

				//���g��j���B
				DeleteGO(this);
			}

			//���W���X�V�B
			CVector3 position = GetPosition();
			position += GetMoveDirection() * kMoveAmount * deltaTime;

			//���W��ݒ�B
			SetPosition(position);
			m_mainEffect->SetPosition(GetPosition());
			m_trigger.SetPosition(GetPosition());
		}

		void CMagicBallOne::OnTriggerEnter(CExtendedDataForRigidActor* otherData) {

			//���C���G�t�F�N�g�𖳌����B
			m_mainEffect->Stop();

			//�g���K�[�ɓ������I�u�W�F�N�g��IGameActor�̃R���C�_�[���ǂ������ׂ�B
			auto rGameActorCollider = otherData->GetOwner<CGameActorCollider>();

			if (rGameActorCollider != nullptr) {

				//�^�[�Q�b�g�ɑ΂��Č��ʂ𔭓��B
				ExecuteFeature(rGameActorCollider->GetGameActor());
			}

			//�G���h�G�t�F�N�g�𐶐��B
			m_endEffect = NewGO<CEffectPlayer>();
			std::string endEffectFilePath = "Assets/Effects/Magics/";
			endEffectFilePath += GetMagicName();
			endEffectFilePath += "_End.efk";

			//�������B
			m_endEffect->Init(nsUtils::GetWideStringFromString(endEffectFilePath).c_str());

			//�����蔻��𖳌����B
			m_trigger.Deactivate();
		}
	}
}