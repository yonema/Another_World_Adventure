#pragma once
#include "FacilityBase.h"
#include "../UI/Institution/Guild/GuildWindowUI.h"

namespace nsAWA
{
	namespace nsFacility
	{
		enum class EnGuildState
		{
			enClose,
			enOpen
		};

		class CGuild : public IFacilityBase
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

			void OnTriggerEnter(CExtendedDataForRigidActor* otherData) override final;

			void OnTriggerStay(CExtendedDataForRigidActor* otherData) override final;

			void OnTriggerExit(CExtendedDataForRigidActor* otherData) override final;

		public:
			constexpr CGuild() = default;
			~CGuild() = default;

		private:
			CFontRenderer* m_enterFont = nullptr;
			EnGuildState m_state = EnGuildState::enClose;
			nsUI::CGuildWindowUI* m_windowUI = nullptr;
		};

	}
}