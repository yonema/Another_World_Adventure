#include "GamePreLoading.h"
#include "Humans/HumanManager.h"
#include "Humans/Human.h"
#include "Monster/MonsterPop/MonsterPopManager.h"
#include "Event/EventManager.h"
#include "Event/EventController.h"
#include "../EngineConfig.h"


namespace nsAWA
{
	CGamePreLoading* CGamePreLoading::m_instance = nullptr;
	const float CGamePreLoading::m_kExtentCullingBoxForDebugDrawLine = 500.0f;

	CGamePreLoading::CGamePreLoading()
	{
		assert(m_instance == nullptr);

		m_instance = this;

		return;
	}

	bool CGamePreLoading::Start()
	{
#ifdef DRAW_COLLISION
		SetCullingBoxForDebugDrawLine(
			m_kExtentCullingBoxForDebugDrawLine, nsMath::CVector3::Zero());

		// ラインのカリングボックスの自動カメラフィット機能の有効化。
		EnableAutoFitCullingBoxToMainCamera();
#endif // DRAW_COLLISION

		m_humanManager = NewGO<nsHumans::CHumanManager>("HumanManager");
		m_humanManager->GenerateBase(true);
		nsHumans::CHuman::SetHumanaManager(m_humanManager);

		m_monsterPopManager =
			NewGO<nsMonster::nsMonsterPop::CMonsterPopManager>("MonsterPopManager");
		m_monsterPopManager->SetHumanManagerRef(*m_humanManager);

		m_eventManager = nsEvent::CEventManager::CreateInstance();

		m_eventController = NewGO<nsEvent::CEventController>("EventController");

		return true;
	}

	void CGamePreLoading::Update(float deltaTime)
	{
		if (m_isLoaded)
		{
			return;
		}



		if (m_humanManager->IsBaseLoaded())
		{
			m_isLoaded = true;
		}

		return;
	}

	void CGamePreLoading::OnDestroy()
	{
		DeleteGO(m_monsterPopManager);
		DeleteGO(m_humanManager);
		nsEvent::CEventManager::DeleteInstance();
		m_eventManager = nullptr;
		DeleteGO(m_eventController);

		return;
	}


}