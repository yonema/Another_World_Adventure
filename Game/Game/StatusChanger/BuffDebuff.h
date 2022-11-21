#pragma once
#include "StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		//�o�t���f�o�t��
		enum class EnBuffOrDebuff {

			enBuff,		//�o�t
			enDebuff,	//�f�o�t

			enNone		//�ݒ�Ȃ�
		};

		//�o�t�E�f�o�t�N���X
		class CBuffDebuff : public CStatusChanger
		{
			//�o�t�f�o�t�����N���X�̓t�����h
			friend class CBuffDebuffBuilder;
		private:

			void Init();

			//void ExecuteAtStart(float deltaTime)override final;
			//void ExecuteAtEnd(float deltaTime)override final;

		public:

			float Apply(EnStatusRef statusRef) {

				//��v����Ȃ�B
				if (m_statusRef == statusRef) {

					//�ŗL�̒l��Ԃ��B
					return m_value;
				}
				//��v���Ă��Ȃ��Ȃ�
				else {
					//���{��Ԃ��B
					return 1.0f;
				}
			}
		private:
			EnBuffOrDebuff m_buffOrDebuff = EnBuffOrDebuff::enNone;		//�o�t���f�o�t��
			EnStatusRef m_statusRef = EnStatusRef::enNone;				//�Q�ƃX�e�[�^�X
			float m_value = 0.0f;		//�����l
		};

		//�o�t�f�o�t�����N���X
		class CBuffDebuffBuilder : public CFeature {

		public:
			void Init(EnBuffOrDebuff buffOrDebuff,
				IGameActor* target,
				EnStatusRef statusRef,
				float value,
				float durationTime
			);

			void Create()override final;
		private:
			EnBuffOrDebuff m_buffOrDebuff = EnBuffOrDebuff::enNone;		//�o�t���f�o�t��
			IGameActor* m_target = nullptr;								//�^�[�Q�b�g
			EnStatusRef m_statusRef = EnStatusRef::enNone;				//�Q�ƃX�e�[�^�X
			float m_value = 0.0f;										//�����l
			float m_durationTime = 0.0f;								//��������
		};
	}
}
