#include "YonemaEnginePreCompile.h"
#include "MonsterCollider.h"
#include "Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr float kMonsterTriggerBoxRadius = 2.0f;		//�g���K�[�̔��a
			constexpr float kMonsterTriggerBoxHeight = 4.0f;		//�g���K�[�̍���

			const CVector3 kMonsterTriggerBoxAddPosition = { 0.0f,7.0f,0.0f };		//�g���K�[�ɉ��Z������W
		}

		void CMonsterCollider::CreateCollider() {

			//�����X�^�[�̃|�C���^���i�[�B
			m_monster = dynamic_cast<CMonster*>(m_gameActor);

			//���W���i�[�B
			m_position = &(m_monster->GetPosition());

			//�g���K�[�ɐݒ肷��ŏI���W���`�B
			CVector3 finalPosition = *m_position;
			finalPosition += kMonsterTriggerBoxAddPosition;

			//�g���K�[�ɐݒ肷���]���`�B
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisZ(), nsMath::YM_PIDIV2);

			//�����蔻����������B
			m_triggerBox.InitAsCapsule<CGameActorCollider>(
				this,
				kMonsterTriggerBoxRadius,
				kMonsterTriggerBoxHeight,
				finalPosition,
				EnPhysicsAttributes::enMonster
				);

			//�g���K�[����]�B
			m_triggerBox.SetRotation(rot);
		}

		void CMonsterCollider::Update() {

			//�g���K�[�ɐݒ肷��ŏI���W���`�B
			CVector3 finalPosition;
			finalPosition = *m_position + kMonsterTriggerBoxAddPosition;

			//���W��ݒ�B
			m_triggerBox.SetPosition(finalPosition);
		}

		void CMonsterCollider::Release() {

			//�����蔻���j���B
			m_triggerBox.Release();
		}
	}
}