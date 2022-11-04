#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//�v���C���[�N���X
		class CPlayer : public IGameObject
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		private:
			void CreatePlayerModel();
		private:
			CModelRenderer* m_modelRenderer = nullptr;	//�v���C���[���f��
		};
	}
}

