#include "YonemaEnginePreCompile.h"
#include "CreateTrigger.h"
#include "Feature/FeatureBuilder.h"
#include "GameActorCollider.h"
#include "GameActor.h"

namespace nsAWA {

	namespace {

		constexpr float kTriggerDurationTimer = 0.5f;	//�g���K�[�̎�������
	}

	void CCreateTrigger::Create(
		IGameActor* creator,
		std::list<std::vector<std::string>> triggerMaterial,
		const CVector3& position,
		const CVector3& forwardDirection
	) {
		//�����҂�ݒ�B
		m_creator = creator;

		//�g���K�[����ݒ�B
		for (auto& material : triggerMaterial) {

			if (material[0] == "SIZE") {

				if (material[1] == "Small") {

					m_triggerInfo.size = 3.0f;
				}
				else if (material[1] == "Medium") {

					m_triggerInfo.size = 5.0f;
				}
				else if (material[1] == "Large") {

					m_triggerInfo.size = 10.0f;
				}
			}

			if (material[0] == "POSITION") {

				m_triggerInfo.position.x += stof(material[1]);
				m_triggerInfo.position.y += stof(material[2]);
				m_triggerInfo.position.z += stof(material[3]);
			}

			if (material[0] == "FEATURE") {

				material.erase(material.begin());

				m_triggerInfo.m_featureList.emplace_back(material);
			}
		}

		//�O�������擾�B
		CVector3 triggerForward = forwardDirection;
		triggerForward.y = 0.0f;
		triggerForward.Normalize();

		//�p�x�����߂�B
		float angle = atan2(-forwardDirection.x, forwardDirection.z);

		//�O�����ɍ��W���ݒ肳���悤�ɉ�]���ďC���B
		CQuaternion rot = CQuaternion::Identity();
		rot.SetRotationY(-angle);
		rot.Apply(m_triggerInfo.position);

		//�g���K�[�𐶐��B
		m_trigger.InitAsBox({ m_triggerInfo.size ,m_triggerInfo.size ,m_triggerInfo.size },
			position + m_triggerInfo.position,
			EnPhysicsAttributes::enPlayerAttack
		);

		//��]��ݒ�B
		m_trigger.SetRotation(rot);

		// TriggerEnter�̃R�[���o�b�N�֐���ݒ�B
		m_trigger.SetOnTriggerEnterFunc(
			[&](CExtendedDataForRigidActor* otherData) {OnTriggerEnter(otherData); });

		//�������Ԃ�ݒ�B
		m_triggerDurationTime = kTriggerDurationTimer;
	}

	void CCreateTrigger::OnDestroy() {

		//�g���K�[��j���B
		m_trigger.Release();
	}

	void CCreateTrigger::Update(float deltaTime) {

		//�^�C�}�[���X�V�B
		m_triggerDurationTime -= deltaTime;

		//�^�C�}�[��0�ɂȂ�����B
		if (m_triggerDurationTime <= 0.0f) {

			//���g���폜�B
			DeleteGO(this);
		}
	}

	void CCreateTrigger::OnTriggerEnter(CExtendedDataForRigidActor* otherData) {

		//�g���K�[�ɓ������I�u�W�F�N�g��IGameActor�̃R���C�_�[���ǂ������ׂ�B
		auto rGameActorCollider = otherData->GetOwner<CGameActorCollider>();

		//���g�̃R���C�_�[�ɓ������Ȃ�B
		if (rGameActorCollider == m_creator->GetGameActorCollider()) {

			//�I���B
			return;
		}

		//IGameActor�̃R���C�_�[��������B
		if (rGameActorCollider != nullptr) {

			//���ʂ𐶐��B
			nsFeature::CFeatureBuilder featureBuilder;
			featureBuilder.CreateFeature(m_creator, rGameActorCollider->GetGameActor(), m_triggerInfo.m_featureList);
		}
	}
}