#pragma once
// そのうち消す予定

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