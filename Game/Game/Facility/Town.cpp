#include "Town.h"
#include "../Humans/HumanManager.h"

namespace nsAWA
{
	namespace nsFacility
	{
		bool CTown::Start()
		{

			return true;
		}

		void CTown::OnDestroy()
		{

			return;
		}

		void CTown::Update(float deltaTime)
		{

			return;
		}

		void CTown::OnTriggerEnter(CExtendedDataForRigidActor* otherData)
		{
			if (otherData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayer)
			{
				return;
			}

			if (m_humanManagerRef == nullptr)
			{
				return;
			}

			m_humanManagerRef->ActivateAllHumans();

			return;
		}

		void CTown::OnTriggerExit(CExtendedDataForRigidActor* otherData)
		{
			if (otherData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayer)
			{
				return;
			}

			if (m_humanManagerRef == nullptr)
			{
				return;
			}

			m_humanManagerRef->DeactivateAllHumans();

			return;
		}



	}
}