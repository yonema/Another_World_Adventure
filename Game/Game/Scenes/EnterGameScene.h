#pragma once
#include "SceneBase.h"
namespace nsAWA
{
	class CGameNowLoading;
}
namespace nsAWA
{
	namespace nsScene
	{
		class CEnterGameScene : public ISceneBase
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

			inline const char* const GetSceneName() const noexcept override final
			{
				return "EnterScene";
			}

		public:
			constexpr CEnterGameScene() = default;
			~CEnterGameScene() = default;

		private:
			CGameNowLoading* m_gameNowLoading = nullptr;

		};

	}
}