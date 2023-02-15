#pragma once
#include "EventCutBase.h"

namespace nsAWA
{
	namespace nsEvent
	{
		class CTutorialEventCut : public IEventCutBase
		{
		public:
			bool UpdateEventCut() noexcept override final;

		private:
			enum class EnTutorialStep
			{
				enWalk,
				enRun,
				enAttack,
				enStep,
				enGuard,
				enSkill,
				enMenu,
				enNum
			};

			static const wchar_t* const m_kText[static_cast<int>(EnTutorialStep::enNum)];

		public:
			CTutorialEventCut();
			~CTutorialEventCut();

		private:
			void ProgressStep();

		private:
			CFontRenderer* m_fontRenderer = nullptr;
			EnTutorialStep m_step = EnTutorialStep::enWalk;
			bool m_inTransition = false;
		};




	}
}