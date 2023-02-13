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

		private:
			static ISceneBase* m_currentScene;
		};


		template<class T>
		T* CreateScene()
		{
			if (ISceneBase::GetCurrentScene())
			{
				DeleteGO(ISceneBase::GetCurrentScene());
				ISceneBase::SetCurrentScene(nullptr);
			}

			T* newScene = NewGO<T>();
			newScene->SetName(newScene->GetSceneName());
			ISceneBase::SetCurrentScene(newScene);

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



	}
}