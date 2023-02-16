#include "YonemaEnginePreCompile.h"
#include "PlayerCollider.h"
#include "Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr float kPlayerTriggerBoxRadius = 2.0f;		//�g���K�[�̔��a
			constexpr float kPlayerTriggerBoxHeight = 4.0f;		//�g���K�[�̍���

			const CVector3 kPlayerTriggerBoxAddPosition = { 0.0f,7.0f,0.0f };		//�g���K�[�ɉ��Z������W
		}

		void CPlayerCollider::CreateCollider() {

			//�v���C���[�̃|�C���^���i�[�B
			m_player = dynamic_cast<CPlayer*>(m_gameActor);

			//���W���i�[�B
			m_position = &(m_player->GetPosition());

			//�g���K�[�ɐݒ肷��ŏI���W���`�B
			CVector3 finalPosition = *m_position;
			finalPosition += kPlayerTriggerBoxAddPosition;

			//�g���K�[�ɐݒ肷���]���`�B
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisZ(), nsMath::YM_PIDIV2);

			//�����蔻����������B
			m_trigger.InitAsCapsule<CGameActorCollider>(
				this,
				kPlayerTriggerBoxRadius,
				kPlayerTriggerBoxHeight,
				finalPosition,
				EnPhysicsAttributes::enPlayer
			);

			//�g���K�[����]�B
			m_trigger.SetRotation(rot);
		}

		void CPlayerCollider::Update() {

			//�g���K�[�ɐݒ肷��ŏI���W���`�B
			CVector3 finalPosition;
			finalPosition = *m_position + kPlayerTriggerBoxAddPosition;

			//���W��ݒ�B
			m_trigger.SetPosition(finalPosition);
		}
	}
}