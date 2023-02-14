#pragma once
namespace nsAWA
{
	class CGameNowLoading : public IGameObject
	{
	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	public:
		constexpr CGameNowLoading() = default;
		~CGameNowLoading() = default;

		void SetExitFunc(const std::function<bool(void)>& exsitFunc)
		{
			m_exitFunc = exsitFunc;
		}

	private:
		CSpriteRenderer* m_spriteRenderer = nullptr;
		CFontRenderer* m_fontRenderer = nullptr;
		float m_degAngle = 0.0f;
		std::function<bool(void)> m_exitFunc = []() {return false; };
	};

}