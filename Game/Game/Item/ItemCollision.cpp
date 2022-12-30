#include "YonemaEnginePreCompile.h"
#include "ItemCollision.h"
#include "../Player/PlayerCollider.h"
#include "../GameActor.h"

namespace nsAWA {

	namespace nsItem {

		namespace {
			
			constexpr float kItemRigidBodyRadius = 3.0f;						//���̂̔��a
			constexpr float kItemTriggerRadius = kItemRigidBodyRadius + 1.0f;	//�g���K�[�̔��a
			constexpr float kExecuteFeatureRadius = 20.0f;	//���ʔ����g���K�[�̔��a
			constexpr float kItemThrowAngle = 30.0f;							//������p�x
			constexpr float kItemThrowPower = 30.0f;							//�����鋭��

			constexpr float kExecuteFeatureTriggerTime = 3.0f;		//���ʂ�^����g���K�[�̌p������
		}

		void CItemCollision::Init(const CVector3& position) {

			//�����蔻����������B
			m_rigidBody.InitAsSphere(kItemRigidBodyRadius, position,EnPhysicsAttributes::enItemRigidBody);
			m_trigger.InitAsSphere(kItemTriggerRadius, m_rigidBody.GetPosition());
			
			//���ʔ͈͂̃g���K�[���������B
			m_featureTrigger.InitAsSphere(kExecuteFeatureRadius, m_rigidBody.GetPosition());

			// TriggerEnter�̃R�[���o�b�N�֐���ݒ�B
			m_trigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) {OnTriggerEnter(otherData); });

			// FeatureTriggerEnter�̃R�[���o�b�N�֐���ݒ�B
			m_featureTrigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) {OnFeatureTriggerEnter(otherData); });

			//���ʔ͈̓g���K�[�͖������B
			m_featureTrigger.Deactivate();
		}

		void CItemCollision::Throw(const CVector3& throwDirection) {

			//����������𐳋K���B
			CVector3 finalThrowDirection = throwDirection;
			finalThrowDirection.Normalize();
			
			//������p�x���v�Z�B
			CQuaternion rot;
			rot.SetRotationDeg(Cross(finalThrowDirection, CVector3::AxisY()), kItemThrowAngle);

			//�����Ɍv�Z���ꂽ�p�x������B
			rot.Apply(finalThrowDirection);

			//�͂������ē�����B
			m_rigidBody.AddForce(finalThrowDirection * kItemThrowPower);

			//���̂�����W���擾���A�g���K�[�ɐݒ�B
			m_trigger.SetPosition(m_rigidBody.GetPosition());
		}

		void CItemCollision::Release() {

			//�e�����蔻���j���B
			m_rigidBody.Release();
			m_trigger.Release();
			m_featureTrigger.Release();
		}

		void CItemCollision::Update(float deltaTime) {

			//�����ɓ������Ă�����B
			if (m_isHit) {

				//���Ԃ����Z�B
				m_executeTriggerTimer += deltaTime;

				//�p�����Ԃ���莞�Ԃ𒴂�����B
				if (m_executeTriggerTimer > kExecuteFeatureTriggerTime) {

					//�I���B
					m_isEnd = true;
				}
			}

			//���W���X�V�B
			m_trigger.SetPosition(m_rigidBody.GetPosition());
		}

		void CItemCollision::OnTriggerEnter(CExtendedDataForRigidActor* otherData) {

			//���ɉ����ɓ������Ă�����B
			if (m_isHit) {

				//�������^�[���B
				return;
			}

			//���g�̍��̂�������B
			if (otherData->GetPhysicsAttribute() == EnPhysicsAttributes::enItemRigidBody) {

				//�������^�[���B
				return;
			}

			//�������A�C�e�����v���C���[�ȊO�̉����i���g�̍��̂������j�ƐڐG�����B
			if (otherData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayer
				&& otherData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayerAttack
				)
			{
				//���ʔ͈̓g���K�[��L�����B
				m_featureTrigger.Activate();
				m_featureTrigger.SetPosition(m_rigidBody.GetPosition());

				//���̔���͔j���B
				m_rigidBody.Deactivate();
				m_trigger.Deactivate();
				
				//�����ɓ��������B
				m_isHit = true;
			}
		}

		void CItemCollision::OnFeatureTriggerEnter(CExtendedDataForRigidActor* otherData) {

			//�g���K�[�ɓ������I�u�W�F�N�g��IGameActor�̃R���C�_�[���ǂ������ׂ�B
			auto rGameActorCollider = otherData->GetOwner<CGameActorCollider>();

			//IGameActor�̃R���C�_�[��������B
			if (rGameActorCollider != nullptr) {

				//���X�g�ɑΏۂ��i�[�B
				m_hitActorList.emplace_back(rGameActorCollider->GetGameActor());
			}
		}
	}
}