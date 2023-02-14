#pragma once
#include "SceneBase.h"
namespace nsAWA
{
	class CGameNowLoading;
	namespace nsHumans
	{
		class CHumanModelRenderer;
	}
}

namespace nsAWA
{
	namespace nsScene
	{
		class COpeningScene : public ISceneBase
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

			inline const char* const GetSceneName() const noexcept override final
			{
				return "OpeningScene";
			}

		public:
			constexpr COpeningScene() = default;
			~COpeningScene() = default;

			static bool IsInitialOpening() noexcept
			{
				return m_initialOpening;
			}

		private:
			static bool m_initialOpening;
			CSkyCubeRenderer* m_skyCubeRenderer = nullptr;
			nsHumans::CHumanModelRenderer* m_humanMR = nullptr;
			CGameNowLoading* m_gameNowLoading = nullptr;
		};

	}
}