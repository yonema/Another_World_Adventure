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

			virtual CFeature* CreateAndReturn() {

				//�ꕔ�̔h���N���X�Ŏg�p�����֐��̂��߁A���N���X�̂��̊֐����Ă΂ꂽ�ꍇ�̓G���[���o�͂���B
				nsGameWindow::MessageBoxError(L"�����������̂�����܂���B");

				return nullptr;
			}

			bool Update(float deltaTime);

			virtual float Apply(EnStatusRef statusRef) { return 1.0f; }
		public:
			void SetDurationTime(float durationTime) {

				//�������Ԃ�ݒ�B
				m_durationTime = durationTime;
			}

		protected:
			virtual void Execute(float deltaTime) {}

		protected:
			float m_durationTime = 0.0f;	//��������
		};
	}
}

