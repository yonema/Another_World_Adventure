#pragma once

namespace nsAWA {

	namespace nsBackGround {

		//�o�b�N�O���E���h�N���X
		class CBackGround : public IGameObject
		{
		public:
			static const char* const m_kObjName_BackGround;		//�o�b�N�O���E���h�N���X�̖��O
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;
		private:
			CPhysicsStaticObject m_physicsStaticObject;		//�����蔻��
			CModelRenderer* m_stageModel = nullptr;			//�n�ʃ��f��
		};
	}
}