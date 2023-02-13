#pragma once
#include "FacilityBase.h"

namespace nsAWA
{
	namespace nsFacility
	{
		class CInn : public IFacilityBase
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;



		public:
			constexpr CInn() = default;
			~CInn() = default;

		private:

		};

	}
}