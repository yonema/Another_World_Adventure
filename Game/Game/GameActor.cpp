#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/FeatureManager.h"
#include "Item/ItemManager.h"
#include "Skill/PassiveSkillManager.h"

namespace nsAWA {

	bool IGameActor::Start() {

		//�p�b�V�u�X�L���Ǘ��N���X�𐶐��B
		m_passiveSkillManager = new nsSkill::CPassiveSkillManager;

		//�p�b�V�u�Ǘ��N���X���������B
		m_passiveSkillManager->Init();

		//���ʊǗ��N���X�𐶐��B
		m_featureManager = new nsFeature::CFeatureManager;

		//�h���N���X�̊J�n�����B
		return StartSub();
	}

	void IGameActor::OnDestroy() {

		//���f����j���B
		DeleteGO(m_modelRenderer);

		//�p�b�V�u�X�L���Ǘ��N���X��j���B
		if (m_passiveSkillManager != nullptr) {

			m_passiveSkillManager->Release();
			
			delete m_passiveSkillManager;
		}

		//�X�e�[�^�X�ω��Ǘ��N���X��j���B
		if (m_featureManager != nullptr) {

			m_featureManager->Release();

			delete m_featureManager;
		}

		//�h���N���X�̔j�������B
		OnDestroySub();
	}

	void IGameActor::UpdateForwardDirection() {

		//��]�s����v�Z�B
		auto mRot = CMatrix::Identity();
		mRot.MakeRotationFromQuaternion(m_rotation);

		//�O������ݒ�B
		m_forwardDirection.x = mRot.m_fMat[2][0];
		m_forwardDirection.y = mRot.m_fMat[2][1];
		m_forwardDirection.z = mRot.m_fMat[2][2];

		//���K���B
		m_forwardDirection.Normalize();
	}

	void IGameActor::Update(float deltaTime) {

		//�q�b�g�X�g�b�v���Ȃ�B
		if (m_isHitStop) {

			//���f���̍��W��ݒ�B
			m_modelRenderer->SetPosition(m_position + m_positionOffset);

			//�I���B
			return;
		}

		//�O�������X�V�B
		UpdateForwardDirection();

		//�p�b�V�u�X�L�����X�V�B
		m_passiveSkillManager->UpdatePassiveSkill();

		//�h���N���X���X�V�B
		UpdateActor(deltaTime);

		//���f���̍��W��ݒ�B
		m_modelRenderer->SetPosition(m_position + m_positionOffset);

		//��]����ݒ�B
		m_modelRenderer->SetRotation(m_rotation);

		//�X�e�[�^�X�ω����X�V�B
		m_featureManager->UpdateFeature(deltaTime);
	}
}