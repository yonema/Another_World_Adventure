#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "../Feature/FeatureManager.h"
#include "BuffDebuff.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			void CBuffDebuff::Init(EnBuffOrDebuff buffOrDebuff,
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

			void CBuffDebuff::Create()
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
				buffDebuff->m_durationTime = m_durationTime;

				//�^�[�Q�b�g�ɂ��o�t�f�o�t����ݒ�B
				buffDebuff->m_target->GetFeatureManager()->AddStatusChanger(buffDebuff);
			}

			CFeature* CBuffDebuff::CreateAndReturn()
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
				buffDebuff->m_durationTime = m_durationTime;

				//�^�[�Q�b�g�ɂ��o�t�f�o�t����ݒ�B
				buffDebuff->m_target->GetFeatureManager()->AddStatusChanger(buffDebuff);

				//�������ꂽ�o�t�f�o�t�������^�[���B
				return buffDebuff;
			}
		}
	}
}