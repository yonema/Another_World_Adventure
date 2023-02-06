#pragma once
#include "../Feature.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			//��Ԉُ�̎��
			enum class EnAbnormalStatusType {

				enPoison,	//��
				enParalysis,	//���

				enNum,		//��Ԉُ�̐�
				enNone		//�ݒ�Ȃ�
			};

			//��Ԉُ�N���X
			class CAbnormalStatus : public CFeature
			{
			public:
				void Create()override final;

				CFeature* CreateAndReturn()override final;

				void Init(
					EnAbnormalStatusType abnormalStatusType,
					int abnormalStatusLevel
				);
			protected:
				virtual void Init() {}

				void Execute(float deltaTime)override {}

				EnAbnormalStatusType GetType()const {

					//��Ԉُ�̎�ނ����^�[���B
					return m_type;
				}

			private:
				EnAbnormalStatusType m_type = EnAbnormalStatusType::enNone;	//��Ԉُ�̎��
				int m_abnormalStatusLevel = 0;			//��Ԉُ탌�x��
			};
		}
	}
}