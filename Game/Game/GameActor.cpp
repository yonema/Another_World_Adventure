#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "AbnormalStatus/AbnormalStatus.h"

namespace nsAWA {

	void IGameActor::AddAbnormalStatus(nsAbnormalStatus::CAbnormalStatus* abnormalStatus) {

		//��Ԉُ��t�^�B
		m_abnormalStatus.emplace_back(abnormalStatus);
	}

	void IGameActor::Update(float deltaTime) {

		//��Ԉُ���X�V�B
		UpdateAbnormalStatus(deltaTime);

		//�h���N���X���X�V�B
		UpdateActor(deltaTime);
	}

	void IGameActor::UpdateAbnormalStatus(float deltaTime) {

		//��Ԉُ�̃��X�g�̃C�e���[�^�����ɎQ�ƁB
		std::list<nsAbnormalStatus::CAbnormalStatus*>::iterator itr;
		for (itr = m_abnormalStatus.begin(); itr != m_abnormalStatus.end(); ) {

			//��Ԉُ���X�V�B
			bool isDead = (*itr)->Update(deltaTime);

			//�I���������B
			if (isDead) {

				//���̏�Ԉُ��j���B
				itr = m_abnormalStatus.erase(itr);

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