#pragma once
namespace nsAWA
{
	namespace nsEvent
	{
		class IEventCutBase : public IGameObject
		{
		public:
			// �A�b�v�f�[�g�͎g�p���Ȃ�
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