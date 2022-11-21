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
		class CAbnormalStatusBuilder : nsUtils::SNoncopyable {

		public:
			void Create(
				EnAbnormalStatusType abnormalStatusType,
				IGameActor* target,
				int abnormalStatusLevel
			);
		};
	}
}