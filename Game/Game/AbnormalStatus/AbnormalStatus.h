#pragma once
#include "../GameActor.h"

namespace nsAWA {

	namespace nsAbnormalStatus {

		//��Ԉُ�̎��
		enum EnAbnormalStatusType {

			enPoison,	//��

			enNum,		//��Ԉُ�̐�
			enNone		//�ݒ�Ȃ�
		};

		//��Ԉُ�N���X
		class CAbnormalStatus : nsUtils::SNoncopyable
		{
			//��Ԉُ퐶���N���X�̓t�����h
			friend class CAbnormalStatusBuilder;
		public:
			bool Update(float deltaTime);

		protected:
			virtual void Init() {}

			virtual void Execute(float deltaTime) = 0;

		protected:
			IGameActor* m_target = nullptr;		//���ʂ������炷�^�[�Q�b�g

		private:
			float m_durationTimer = 0.0f;		//��������
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