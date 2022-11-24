#pragma once

namespace nsAWA
{
	namespace nsScenes
	{
		class SpriteLevelTestScene : public IGameObject
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

			constexpr SpriteLevelTestScene() = default;

			~SpriteLevelTestScene() = default;

		private:
		};
	}
}
