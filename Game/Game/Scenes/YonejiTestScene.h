#pragma once
#include "SceneBase.h"

// そのうち消す予定

namespace nsAWA
{
	class CLoadGame;
	namespace nsWorld
	{
		class CWorld;
	}

	namespace nsEvent
	{
		class CEventFlow;
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

			constexpr void Tutorial() noexcept
			{
				m_isTutorial = true;
			}

			bool IsLoaded() const noexcept;

		private:

			void InitAfterBaseLoaded(float deltaTime);

		private:
			CLoadGame* m_loadGame = nullptr;
			nsWorld::CWorld* m_world = nullptr;
			bool m_isTutorial = false;
		};

	}
}