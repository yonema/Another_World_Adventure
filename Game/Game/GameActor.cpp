#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/FeatureManager.h"
#include "Item/ItemManager.h"
#include "Skill/PassiveSkillManager.h"

namespace nsAWA {

	bool IGameActor::Start() {

		//�A�C�e���Ǘ��N���X�𐶐��B
		m_itemManager = new nsItem::CItemManager;

		//�A�C�e���Ǘ��N���X���������B
		m_itemManager->Init(this);

		//�p�b�V�u�X�L���Ǘ��N���X�𐶐��B
		m_passiveSkillManager = new nsSkill::CPassiveSkillManager;

		//���ʊǗ��N���X�𐶐��B
		m_featureManager = new nsFeature::CFeatureManager;

		//�h���N���X�̊J�n�����B
		return StartSub();
	}

	void IGameActor::OnDestroy() {

		//�j�������B

		if (m_itemManager != nullptr) {

			//�A�C�e���Ǘ��N���X��j���B
			delete m_itemManager;
		}

		if (m_passiveSkillManager != nullptr) {

			//�p�b�V�u�X�L���Ǘ��N���X��j���B
			delete m_passiveSkillManager;
		}

		//�h���N���X�̔j�������B
		OnDestroySub();
	}

	void IGameActor::Update(float deltaTime) {

		//�q�b�g�X�g�b�v���Ȃ�B
		if (m_hitStopTimer > FLT_EPSILON) {

			//�^�C�}�[���X�V�B
			m_hitStopTimer -= deltaTime;

			//�I���B
			return;
		}
		else {

			//�q�b�g�X�g�b�v�^�C�}�[���������B
			m_hitStopTimer = 0.0f;

			//�A�j���[�V�������x�����ɖ߂��B
			m_modelRenderer->SetAnimationSpeed(1.0f);
		}

		//�p�b�V�u�X�L�����X�V�B
		m_passiveSkillManager->UpdatePassiveSkill();

		//�h���N���X���X�V�B
		UpdateActor(deltaTime);

		//�X�e�[�^�X�ω����X�V�B
		m_featureManager->UpdateFeature(deltaTime);
	}
}