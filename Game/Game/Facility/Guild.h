#pragma once
#include "FacilityBase.h"

namespace nsAWA
{
	namespace nsFacility
	{
		class CGuild : public IFacilityBase
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;


		public:
			constexpr CGuild() = default;
			~CGuild() = default;

		private:
		};

	}
}