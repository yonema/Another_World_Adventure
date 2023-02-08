#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			//�o�t���f�o�t��
			enum class EnBuffOrDebuff {

				enBuff,		//�o�t
				enDebuff,	//�f�o�t

				enNone		//�ݒ�Ȃ�
			};

			//�o�t�E�f�o�t�N���X
			class CBuffDebuff : public CFeature
			{
			public:
				void Init(const std::string& buffOrDebuff,
					const std::string& statusRef,
					float value,
					float durationTime
				);

				void Create()override final;

				float Apply(EnStatusRef statusRef) {

					//��v����Ȃ�B
					if (m_statusRef == statusRef) {

						//�ŗL�̒l��Ԃ��B
						return m_value;
					}
					//��v���Ă��Ȃ��Ȃ�
					else {
						//�ω��Ȃ��B
						return 0.0f;
					}
				}

			private:
				EnBuffOrDebuff GetBuffOrDebuff(const std::string& buffOrDebuff)const;

				EnStatusRef GetStatusRef(const std::string& statusRef)const;

			private:
				EnBuffOrDebuff m_buffOrDebuff = EnBuffOrDebuff::enNone;		//�o�t���f�o�t��
				EnStatusRef m_statusRef = EnStatusRef::enNone;				//�Q�ƃX�e�[�^�X
				float m_value = 0.0f;		//�����l
			};
		}
	}
}
