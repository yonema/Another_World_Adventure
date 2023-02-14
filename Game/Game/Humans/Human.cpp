#include "Human.h"
#include "HumanTable.h"
#include "HumanManager.h"

namespace nsAWA
{
	namespace nsHumans
	{
		CHumanManager* CHuman::m_humanManager = nullptr;

		bool CHuman::Start()
		{

			return true;
		}

		void CHuman::Update(float deltaTime)
		{
			switch (m_loadingState)
			{
			case EnLoadingState::enBeforeLoading:
				break;
			case EnLoadingState::enNowLoading:
				if (m_humanMR->GetModelRenderer()->IsLoadingAsynchronous() != true)
				{
					ChangeLoadingState(EnLoadingState::enAfterLoading);
				}
				break;
			case EnLoadingState::enAfterLoading:
				break;
			}
			return;
		}

		void CHuman::OnDestroy()
		{
			Release();

			return;
		}

		void CHuman::Init(
			const char* name,
			const CVector3& position,
			const CQuaternion& rotation,
			const char* filePath
		)
		{
			m_name = name;

			Release();

			m_humanMR = NewGO<CHumanModelRenderer>(name);
			m_humanMR->Init(name, position, rotation, filePath);

			ChangeLoadingState(EnLoadingState::enNowLoading);
			
			CheckEnableTalking();


			return;
		}

		void CHuman::Release()
		{
			//@attention ‚±‚ÌŠÖ”‚Í•¡”‰ñŒÄ‚Î‚ê‚Ä‚à–â‘è‚È‚¢‚æ‚¤‚É‚·‚é

			if (m_humanMR)
			{
				m_humanMR->Release();
				DeleteGO(m_humanMR);
				m_humanMR = nullptr;
			}

			return;
		}

		void CHuman::CheckEnableTalking()
		{
			auto itr = g_kNameToCsvFilePathParts.find(m_name);
			if (itr == g_kNameToCsvFilePathParts.end())
			{
				m_enableTalking = false;
				return;
			}

			m_enableTalking = true;

			return;
		}


		void CHuman::ChangeLoadingState(EnLoadingState newState)
		{
			if (m_loadingState == newState)
			{
				return;
			}

			m_loadingState = newState;

			switch (m_loadingState)
			{
			case EnLoadingState::enBeforeLoading:
				break;
			case EnLoadingState::enNowLoading:
				break;
			case EnLoadingState::enAfterLoading:
				if (m_humanManager != nullptr)
				{
					if (m_humanManager->IsPlayerInTown() != true)
					{
						HumanDeactivate();
					}
				}
				break;
			}


			return;
		}




	}
}
