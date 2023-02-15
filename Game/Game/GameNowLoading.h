#pragma once
namespace nsAWA
{
	class CGameNowLoading : public IGameObject
	{
	private:
		static const int m_kNumIconAnims = 8;
		static const float m_kIconAnimSwitchTime;

	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	public:
		constexpr CGameNowLoading() = default;
		~CGameNowLoading() = default;

		inline void SetExitFunc(const std::function<bool(void)>& exsitFunc)
		{
			m_exitFunc = exsitFunc;
		}

		constexpr void SetEnableFadeInOnDestroy(bool enableFadeIn) noexcept
		{
			m_enableFadeInOnDestroy = enableFadeIn;
		}

	private:
		CSpriteRenderer* m_spriteRenderer = nullptr;
		std::array< CSpriteRenderer*, m_kNumIconAnims> m_iconAnimSRArray = {};
		CFontRenderer* m_fontRenderer = nullptr;
		std::function<bool(void)> m_exitFunc = []() {return false; };
		int m_iconAnimIdx = 0;
		float m_timer = 0.0f;
		bool m_enableFadeInOnDestroy = true;
	};

}