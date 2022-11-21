#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "BuffDebuff.h"
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsStatusChanger {

		void CBuffDebuff::Init() {

		}

		void CBuffDebuffBuilder::Create(
			EnBuffOrDebuff buffOrDebuff,
			IGameActor* target,
			EnStatusRef statusRef,
			float value,
			float durationTime
		)
		{

			//�o�t�f�o�t�N���X�𐶐��B
			CBuffDebuff* buffDebuff = new CBuffDebuff;

			//�o�t���f�o�t���ݒ�B
			buffDebuff->m_buffOrDebuff = buffOrDebuff;

			//�Q�ƃX�e�[�^�X��ݒ�B
			buffDebuff->m_statusRef = statusRef;

			//�����l��ݒ�B
			buffDebuff->m_value = value;

			//�^�[�Q�b�g��ݒ�B
			buffDebuff->m_target = target;

			//�������Ԃ�ݒ�B
			buffDebuff->m_durationTimer = durationTime;

			//���������������s�B
			buffDebuff->Init();

			//�^�[�Q�b�g�ɂ���Ԉُ��ݒ�B
			target->AddStatusChanger(buffDebuff);
		}
	}
}