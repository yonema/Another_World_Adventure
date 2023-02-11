#pragma once
#include "SceneBase.h"

// ���̂��������\��

namespace nsAWA
{
	class CLoadGame;
	namespace nsWorld
	{
		class CWorld;
	}
}

namespace nsAWA
{
	namespace nsScene
	{
		class CYonejiTestScene : public ISceneBase
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

			inline const char* const GetSceneName() const noexcept override final
			{
				return "YonejiTestScene";
			}

		public:
			constexpr CYonejiTestScene() = default;
			~CYonejiTestScene() = default;

		private:

			void InitAfterBaseLoaded(float deltaTime);

		private:
			CLoadGame* m_loadGame = nullptr;
			nsWorld::CWorld* m_world = nullptr;
		};

	}
}