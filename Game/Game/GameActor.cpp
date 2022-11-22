#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/feature.h"

namespace nsAWA {

	void IGameActor::AddStatusChanger(nsFeature::CFeature* statusChanger) {

		//�X�e�[�^�X�ω���t�^�B
		m_feature.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

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
}