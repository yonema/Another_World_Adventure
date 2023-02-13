#pragma once
#include "SceneBase.h"
namespace nsAWA
{
	namespace nsUI
	{
		class CMenuBaseUI;
	}
}

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
			void TestMenu();

			void TestDeleteMenu();

		private:
			nsUI::CMenuBaseUI* m_menuBaseUI = nullptr;
			bool m_flagCreateMenuBaseUI = false;
		};

	}
}