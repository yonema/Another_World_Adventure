#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "BuffDebuff.h"
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsStatusChanger {

		void CBuffDebuff::Init() {

		}

		void CBuffDebuffBuilder::Init(EnBuffOrDebuff buffOrDebuff,
			IGameActor* target,
			EnStatusRef statusRef,
			float value,
			float durationTime
		) {
			//�����������B
			m_buffOrDebuff = buffOrDebuff;
			m_target = target;
			m_statusRef = statusRef;
			m_value = value;
			m_durationTime = durationTime;
		}

		void CBuffDebuffBuilder::Create()
		{

			//�o�t�f�o�t�N���X�𐶐��B
			CBuffDebuff* buffDebuff = new CBuffDebuff;

			//�o�t���f�o�t���ݒ�B
			buffDebuff->m_buffOrDebuff = m_buffOrDebuff;

			//�Q�ƃX�e�[�^�X��ݒ�B
			buffDebuff->m_statusRef = m_statusRef;

			//�����l��ݒ�B
			buffDebuff->m_value = m_value;

			//�^�[�Q�b�g��ݒ�B
			buffDebuff->m_target = m_target;

			//�������Ԃ�ݒ�B
			buffDebuff->m_durationTimer = m_durationTime;

			//���������������s�B
			buffDebuff->Init();

			//�^�[�Q�b�g�ɂ���Ԉُ��ݒ�B
			buffDebuff->m_target->AddStatusChanger(buffDebuff);
		}
	}
}