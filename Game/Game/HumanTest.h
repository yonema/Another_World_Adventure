#pragma once
// ÇªÇÃÇ§Çøè¡Ç∑ó\íË

namespace nsAWA
{
	class CHumanTest : public IGameObject
	{
	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	public:
		constexpr CHumanTest() = default;
		~CHumanTest() = default;

	private:

	};

}