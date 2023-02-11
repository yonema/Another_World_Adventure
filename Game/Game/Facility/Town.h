#pragma once
#include "FacilityBase.h"
namespace nsAWA
{
	namespace nsHumans
	{
		class CHumanManager;
	}
}

namespace nsAWA
{
	namespace nsFacility
	{
		class CTown : public IFacilityBase
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

			void OnTriggerEnter(CExtendedDataForRigidActor* otherData) override final;

			void OnTriggerExit(CExtendedDataForRigidActor* otherData) override final;


		public:
			constexpr CTown() = default;
			~CTown() = default;

			constexpr void SetHumanManagerRef(nsHumans::CHumanManager* humanManagerRef) noexcept
			{
				m_humanManagerRef = humanManagerRef;
			}
			
		private:
			nsHumans::CHumanManager* m_humanManagerRef = nullptr;
		};

	}
}