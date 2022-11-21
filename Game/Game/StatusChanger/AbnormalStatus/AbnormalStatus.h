#pragma once
#include "../StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		//��Ԉُ�̎��
		enum class EnAbnormalStatusType {

			enPoison,	//��

			enNum,		//��Ԉُ�̐�
			enNone		//�ݒ�Ȃ�
		};

		//��Ԉُ�N���X
		class CAbnormalStatus : public CStatusChanger
		{
			//��Ԉُ퐶���N���X�̓t�����h
			friend class CAbnormalStatusBuilder;

		protected:
			virtual void Init() {}

			void ExecuteAtStart(float deltaTime)override{}

		private:
			EnAbnormalStatusType m_type = EnAbnormalStatusType::enNone;	//��Ԉُ�̎��
		};

		//��Ԉُ퐶���N���X
		class CAbnormalStatusBuilder : public CFeature {

		public:
			void Init(
				EnAbnormalStatusType abnormalStatusType,
				IGameActor* target,
				int abnormalStatusLevel
			);

			void Create()override final;
		private:
			EnAbnormalStatusType m_abnormalStatusType = EnAbnormalStatusType::enNone;	//��Ԉُ�̎��
			IGameActor* m_target = nullptr;			//�^�[�Q�b�g
			int m_abnormalStatusLevel = 0;			//��Ԉُ탌�x��
		};
	}
}