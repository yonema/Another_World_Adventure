#pragma once
namespace nsAWA
{
	namespace nsEvent
	{
		class CEventFlow;
	}
}


namespace nsAWA
{
	namespace nsEvent
	{
		class CEventController : public IGameObject
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CEventController() = default;
			~CEventController() = default;

			void InitCurrentEventFlowMap();

			inline CEventFlow* GetEventFlow(const std::string& eventName)
			{
				auto itr = m_currentEventFlowMap.find(eventName);
				if (itr == m_currentEventFlowMap.end())
				{
					return nullptr;
				}

				return itr->second;
			}

		private:
			std::unordered_map<std::string, CEventFlow*> m_currentEventFlowMap = {};
		};

	}
}