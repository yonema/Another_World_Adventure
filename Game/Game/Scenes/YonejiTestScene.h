#pragma once
#include "SceneBase.h"

// ÇªÇÃÇ§Çøè¡Ç∑ó\íË

namespace nsAWA
{
	class CLoadGame;
	namespace nsHumans
	{
		class CHumanManager;
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
			CLevel3D m_level3D = {};
			nsHumans::CHumanManager* m_humanManager = nullptr;
			bool m_isLevelLoaded = false;
			CLoadGame* m_loadGame = nullptr;

			CFontRenderer* m_nowLoadingFR = nullptr;
		};

	}
}