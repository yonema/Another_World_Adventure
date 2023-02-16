#pragma once
#include "FacilityBase.h"
#include "../UI/Institution/Inn/InnWindowUI.h"

namespace nsAWA
{
	namespace nsFacility
	{
		enum class EnFacilityState
		{
			enClose,
			enOpen
		};

		class CInn : public IFacilityBase
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

			void OnTriggerEnter(CExtendedDataForRigidActor* otherData) override final;

			void OnTriggerStay(CExtendedDataForRigidActor* otherData) override final;

			void OnTriggerExit(CExtendedDataForRigidActor* otherData) override final;
		public:
			constexpr CInn() = default;
			~CInn() = default;
		private:
			CFontRenderer* m_enterFont = nullptr;
			EnFacilityState m_state = EnFacilityState::enClose;
			nsUI::CInnWindowUI* m_windowUI = nullptr;
		};

	}
}