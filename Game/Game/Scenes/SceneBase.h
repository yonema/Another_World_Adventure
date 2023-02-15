#pragma once
namespace nsAWA
{
	namespace nsScene
	{
		class ISceneBase : public IGameObject
		{
		public:
			virtual inline const char* const GetSceneName() const noexcept = 0;

		public:
			constexpr ISceneBase() = default;
			~ISceneBase() = default;

			static inline void SetCurrentScene(ISceneBase* scene) noexcept
			{
				m_currentScene = scene;
			}

			static inline ISceneBase* GetCurrentScene() noexcept
			{
				return m_currentScene;
			}

			static inline bool IsNowCreating() noexcept
			{
				return m_nowCreating;
			}

			static inline void SetNowCreating(bool nowCreating) noexcept
			{
				m_nowCreating = nowCreating;
			}

		private:
			static ISceneBase* m_currentScene;
			static bool m_nowCreating;
		};


		template<class T>
		T* CreateScene()
		{
			if (ISceneBase::IsNowCreating())
			{
				return nullptr;
			}

			ISceneBase::SetNowCreating(true);

			if (ISceneBase::GetCurrentScene())
			{
				DeleteGO(ISceneBase::GetCurrentScene());
				ISceneBase::SetCurrentScene(nullptr);
			}

			T* newScene = NewGO<T>();
			newScene->SetName(newScene->GetSceneName());
			ISceneBase::SetCurrentScene(newScene);


			ISceneBase::SetNowCreating(false);

			return newScene;
		}

		static void DeleteCurrentScene()
		{
			if (ISceneBase::GetCurrentScene())
			{
				DeleteGO(ISceneBase::GetCurrentScene());
				ISceneBase::SetCurrentScene(nullptr);
			}
		}


		template<class T>
		void CreateSceneWithFade()
		{
			if (ISceneBase::IsNowCreating())
			{
				return;
			}

			ISceneBase::SetNowCreating(true);

			Fade()->FadeOut();

			InvokeFunc(
				[&]()
				{
					if (ISceneBase::GetCurrentScene())
					{
						DeleteGO(ISceneBase::GetCurrentScene());
						ISceneBase::SetCurrentScene(nullptr);
					}

					T* newScene = NewGO<T>();
					newScene->SetName(newScene->GetSceneName());
					ISceneBase::SetCurrentScene(newScene);

					Fade()->FadeIn();

					ISceneBase::SetNowCreating(false);
				},
				Fade()->GetDefaultFadeTime() + 0.5f
			);


			return;
		}



	}
}