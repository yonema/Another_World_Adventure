#include "Town.h"
#include "../Humans/HumanManager.h"
#include "../Player/PlayerCollider.h"
#include "../Player/Player.h"

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

			auto* actorCollider = otherData->GetOwner<CGameActorCollider>();
			auto* playerCollider = dynamic_cast<nsPlayer::CPlayerCollider*>(actorCollider);

			if (playerCollider)
			{
				auto* player = playerCollider->GetPlayer();
				if (player)
				{
					player->SetIsInTown(true);
				}
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

			auto* actorCollider = otherData->GetOwner<CGameActorCollider>();
			auto* playerCollider = dynamic_cast<nsPlayer::CPlayerCollider*>(actorCollider);

			if (playerCollider)
			{
				auto* player = playerCollider->GetPlayer();
				if (player)
				{
					player->SetIsInTown(false);
				}
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