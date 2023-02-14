#pragma once
#include "SceneBase.h"

namespace nsAWA
{
	namespace nsScene
	{
		class CMainGameScene : public ISceneBase
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

			inline const char* const GetSceneName() const noexcept override final
			{
				return "MainGameScene";
			}

		public:
			constexpr CMainGameScene() = default;
			~CMainGameScene() = default;

		private:

		};

	}
}