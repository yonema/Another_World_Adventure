#pragma once
#include "FacilityBase.h"

namespace nsAWA
{
	namespace nsFacility
	{
		class CForge : public IFacilityBase
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;


		public:
			constexpr CForge() = default;
			~CForge() = default;


		private:
		};

	}
}