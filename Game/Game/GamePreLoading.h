#pragma once
namespace nsAWA
{
	namespace nsHumans
	{
		class CHumanManager;
	}
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			class CMonsterPopManager;
		}
	}
	namespace nsEvent
	{
		class CEventManager;
		class CEventController;
	}
}

namespace nsAWA
{
	class CGamePreLoading : public IGameObject
	{
	private:
		static const float m_kExtentCullingBoxForDebugDrawLine;

	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	public:
		CGamePreLoading();
		~CGamePreLoading() = default;

		static auto* GetInstance() noexcept
		{
			return m_instance;
		}

		constexpr auto* GetHumanManager() noexcept
		{
			return m_humanManager;
		}

		constexpr auto* GetMonsterPopManager() noexcept
		{
			return m_monsterPopManager;
		}

		constexpr auto* GetEventManager() noexcept
		{
			return m_eventManager;
		}

		constexpr auto* GetEventController() noexcept
		{
			return m_eventController;
		}

		constexpr bool IsLoaded() const noexcept
		{
			return m_isLoaded;
		}

	private:
		static CGamePreLoading* m_instance;
		nsHumans::CHumanManager* m_humanManager = nullptr;
		nsMonster::nsMonsterPop::CMonsterPopManager* m_monsterPopManager = nullptr;
		nsEvent::CEventManager* m_eventManager = nullptr;
		nsEvent::CEventController* m_eventController = nullptr;
		bool m_isLoaded = false;
	};

}