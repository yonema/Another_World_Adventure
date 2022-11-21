#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "StatusChanger/StatusChanger.h"

namespace nsAWA {

	void IGameActor::AddStatusChanger(nsFeature::nsStatusChanger::CStatusChanger* statusChanger) {

		//�X�e�[�^�X�ω���t�^�B
		m_statusChanger.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

		//�X�e�[�^�X�ω����X�V�B
		UpdateStatusChangerAtStart(deltaTime);

		//�h���N���X���X�V�B
		UpdateActor(deltaTime);

		//�X�e�[�^�X�ω����X�V�B
		UpdateStatusChangerAtEnd(deltaTime);
	}

	void IGameActor::UpdateStatusChangerAtStart(float deltaTime) {

		//�X�e�[�^�X�ω��̃��X�g�̃C�e���[�^�����ɎQ�ƁB
		for (const auto& statusChanger : m_statusChanger) {

			//�X�e�[�^�X�ω����X�V�B
			statusChanger->UpdateAtStart(deltaTime);
		}
	}

	void IGameActor::UpdateStatusChangerAtEnd(float deltaTime) {

		//�X�e�[�^�X�ω��̃��X�g�̃C�e���[�^�����ɎQ�ƁB
		std::list<nsFeature::nsStatusChanger::CStatusChanger*>::iterator itr;
		for (itr = m_statusChanger.begin(); itr != m_statusChanger.end(); ) {

			//�X�e�[�^�X�ω����X�V�B
			bool isDead = (*itr)->UpdateAtEnd(deltaTime);

			//�I���������B
			if (isDead) {

				//���̃X�e�[�^�X�ω���j���B
				itr = m_statusChanger.erase(itr);

				//�j�����ꂽ���Ƃɂ��A���Ɏ��̃C�e���[�^�������Ă���̂ňڂ鏈�����X�L�b�v�B
				continue;
			}

			//���̃C�e���[�^�Ɉڂ�B
			itr++;
		}
	}
}