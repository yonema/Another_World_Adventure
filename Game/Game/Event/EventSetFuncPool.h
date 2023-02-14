#pragma once
namespace nsAWA
{
	namespace nsEvent
	{
		class CEventSetFuncPool : public IGameObject
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			CEventSetFuncPool();
			~CEventSetFuncPool() = default;

			constexpr const auto& GetSetFuncListMap() const noexcept
			{
				return m_setFuncListMap;
			}

		private:
			std::unordered_map< std::string, std::vector<std::function<bool(void)>>> m_setFuncListMap = {};
		};

	}
}