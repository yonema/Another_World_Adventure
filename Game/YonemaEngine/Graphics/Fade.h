#pragma once
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsRenderers
		{
			class CSpriteRenderer;
		}
	}
}

namespace nsYMEngine
{
	namespace nsGraphics
	{
		class CFade : public nsGameObject::IGameObject
		{
		public:
			enum class EnFadeState
			{
				enFadingOut,
				enFadeOutEnd,
				enFadingIn,
				enFadeInEnd
			};

		private:
			static const float m_kDefaultFadeTime;

		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

		public:
			CFade()
			{
				if (m_instance != nullptr)
				{
					nsGameWindow::MessageBoxError(L"CFadeクラスのインスタンスは1つしか作成できません。");
					return;
				}
				m_instance = this;
			}
			~CFade()
			{
				m_instance = nullptr;
			}

			void FadeOut(float time = -1.0f) noexcept;

			void FadeIn(float time = -1.0f) noexcept;

			constexpr EnFadeState GetFadeState() const noexcept
			{
				return m_fadeState;
			}

			constexpr float GetDefaultFadeTime() const noexcept
			{
				return m_kDefaultFadeTime;
			}

		private:
			inline void SetFadeTime(float time) noexcept
			{
				if (time >= 0.0f)
				{
					m_fadeTime = time;
					m_fadeInitialTime = time;
				}
				else
				{
					m_fadeTime = m_kDefaultFadeTime;
					m_fadeInitialTime = m_kDefaultFadeTime;
				}
			}
			void UpdateFading(float deltaTime) noexcept;

			void SetFadeAlpha() noexcept;

		private:
			static CFade* m_instance;
			nsRenderers::CSpriteRenderer* m_fadeSR = nullptr;
			float m_fadeTime = 0.0f;
			float m_fadeInitialTime = 0.0f;
			EnFadeState m_fadeState = EnFadeState::enFadeInEnd;
		};

	}
}