#pragma once
#include "SceneBase.h"

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

		private:
			CFontRenderer* m_fontRenderer = nullptr;
		};

	}
}