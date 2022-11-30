#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/feature.h"
#include "Skill/PassiveSkill.h"
#include "Item/ItemManager.h"

namespace nsAWA {

	bool IGameActor::Start() {

		//�A�C�e���Ǘ��N���X�𐶐��B
		m_itemManager = new nsItem::CItemManager;

		//�h���N���X�̊J�n�����B
		return StartSub();
	}

	void IGameActor::OnDestroy() {

		//�j�������B

		if (m_itemManager != nullptr) {

			//�A�C�e���Ǘ��N���X��j���B
			delete m_itemManager;
		}

		//�h���N���X�̔j������.
		OnDestroySub();
	}

	void IGameActor::AddStatusChanger(nsFeature::CFeature* statusChanger) {

		//�X�e�[�^�X�ω���t�^�B
		m_feature.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

		//�p�b�V�u�X�L�����X�V�B
		UpdatePassiveSkill();

		//�h���N���X���X�V�B
		UpdateActor(deltaTime);

		//�X�e�[�^�X�ω����X�V�B
		UpdateFeature(deltaTime);
	}

	void IGameActor::UpdateFeature(float deltaTime) {

		//�X�e�[�^�X�ω��̃��X�g�̃C�e���[�^�����ɎQ�ƁB
		for (auto itr = m_feature.begin(); itr != m_feature.end(); ) {

			//�X�e�[�^�X�ω��̋@�\���X�V�B
			bool isDead = (*itr)->Update(deltaTime);

			//�I���������B
			if (isDead) {

				//���̃X�e�[�^�X�ω���j���B
				itr = m_feature.erase(itr);

				//�j�����ꂽ���Ƃɂ��A���Ɏ��̃C�e���[�^�������Ă���̂ňڂ鏈�����X�L�b�v�B
				continue;
			}

			//���̃C�e���[�^�Ɉڂ�B
			itr++;
		}
	}

	void IGameActor::AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill) {

		//�ő�\�������𒴂��ĂȂ��Ȃ�B
		if (m_passiveSkill.size() < m_passiveSkillMaxNum) {

			//�p�b�V�u�X�L���𑕒�����B
			m_passiveSkill.emplace_back(passiveSkill);
		}
	}

	void IGameActor::UpdatePassiveSkill() {

		//�p�b�V�u�X�L�������ɎQ�ƁB
		for (const auto& passiveSkill : m_passiveSkill) {

			//�X�V�B
			passiveSkill->Update();
		}
	}
}