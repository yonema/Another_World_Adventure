#pragma once
#include "Feature.h"

namespace nsAWA {

	//�G�C���A�X�錾
	class IGameActor;

	namespace nsStatusChanger {

		//�^�[�Q�b�g�̎Q�ƃX�e�[�^�X
		enum class EnStatusRef {

			enAttack,		//�����U����
			enDeffence,		//�����h���

			enNone			//�ݒ�Ȃ�
		};

		//�X�e�[�^�X�ω��N���X
		class CStatusChanger : nsUtils::SNoncopyable
		{
		public:
			
			void UpdateAtStart(float deltaTime);

			/**
			 * @brief �߂�l�ł͂��̃X�e�[�^�X�ω����I����������Ԃ��B
			*/
			bool UpdateAtEnd(float deltaTime);
		protected:
			virtual void ExecuteAtStart(float deltaTime){}
			virtual void ExecuteAtEnd(float deltaTime){}

		public:
			virtual float Apply(nsStatusChanger::EnStatusRef statusRef) { return 1.0f; }

		protected:
			float m_durationTimer = 0.0f;		//��������
			IGameActor* m_target = nullptr;		//���ʂ������炷�^�[�Q�b�g
		};
	}
}

