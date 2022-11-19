#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "StatusChanger/StatusChanger.h"

namespace nsAWA {

	void IGameActor::AddStatusChanger(nsStatusChanger::CStatusChanger* statusChanger) {

		//�X�e�[�^�X�ω���t�^�B
		m_statusChanger.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

		//�X�e�[�^�X�ω����X�V�B
		UpdateStatusChanger(deltaTime);

		//�h���N���X���X�V�B
		UpdateActor(deltaTime);
	}

	void IGameActor::UpdateStatusChanger(float deltaTime) {

		//�X�e�[�^�X�ω��̃��X�g�̃C�e���[�^�����ɎQ�ƁB
		std::list<nsStatusChanger::CStatusChanger*>::iterator itr;
		for (itr = m_statusChanger.begin(); itr != m_statusChanger.end(); ) {

			//�X�e�[�^�X�ω����X�V�B
			bool isDead = (*itr)->Update(deltaTime);

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


		
		//for (const auto& as : m_abnormalStatus) {

		//	//��Ԉُ���X�V�B
		//	bool isDead = as->Update(deltaTime);

		//	//����ł���Ȃ�j���B
		//	if (isDead) {
		//		m_abnormalStatus.erase(as);
		//	}

		//	
		//}
	}
}