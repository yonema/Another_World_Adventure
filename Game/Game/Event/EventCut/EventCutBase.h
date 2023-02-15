#pragma once
namespace nsAWA
{
	namespace nsEvent
	{
		class IEventCutBase : public IGameObject
		{
		public:
			// アップデートは使用しない
			void Update(float deltaTime) override final {};

		public:
			constexpr IEventCutBase() = default;
			virtual ~IEventCutBase() = default;

		public:
			virtual bool UpdateEventCut() = 0;

		private:

		};









	}
}