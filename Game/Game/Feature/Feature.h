#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;

	namespace nsFeature {

		//�^�[�Q�b�g�̎Q�ƃX�e�[�^�X
		enum class EnStatusRef {

			enAttack,		//�����U����
			enDeffence,		//�����h���

			enNone			//�ݒ�Ȃ�
		};

		//�@�\�N���X
		class CFeature : nsUtils::SNoncopyable
		{
		public:
			virtual void Create() = 0;

			void Release();

			bool Update(float deltaTime);

		public:
			void SetDurationTime(float durationTime) {

				//�������Ԃ�ݒ�B
				m_durationTime = durationTime;
			}

			void SetTarget(IGameActor* target) {

				//���ʂ̑Ώۂ�ݒ�B
				m_target = target;
			}

			void SetCreator(IGameActor* creator) {

				//���ʂ̐����҂�ݒ�B
				m_creator = creator;
			}

		protected:
			virtual void Execute(float deltaTime){}

		protected:
			float m_durationTime = 0.0f;	//��������
			IGameActor* m_target = nullptr;	//���ʂ̑Ώ�
			IGameActor* m_creator = nullptr;//���ʂ̐�����
		};
	}
}

