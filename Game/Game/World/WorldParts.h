#pragma once
#include "TRSListMap.h"

namespace nsAWA
{
	namespace nsHumans
	{
		class CHumanManager;
	}
	namespace nsFacility
	{
		class IFacilityBase;
	}
}

namespace nsAWA
{
	namespace nsWorld
	{
		class CWorldParts : nsUtils::SNoncopyable
		{
		private:
			enum EnPartsType
			{
				enTown,
				enBuilding,
				enMeadow,
				enMountain,
				enForest,
				enFacility,
				enNum
			};

			static const char* const m_kPartsPrefixArray[static_cast<int>(EnPartsType::enNum)];
			static const char* const m_kFacilityPrefix;

		public:
			constexpr CWorldParts() = default;
			~CWorldParts();

			bool PushWorldData(
				const std::string& objName, 
				const CVector3& pos, 
				const CQuaternion& rot, 
				const CVector3& scale
			);

			void Build(nsHumans::CHumanManager* humanManager);

		private:

			void Terminate();

			void BuildModel();

			void BuildFacility(nsHumans::CHumanManager* humanManager);

			void UnexpectedLevelObject(const std::string& objName) const noexcept;


		private:
			TRSListMap m_modelTRSListMap = {};
			TRSMap m_facilityTRSMap = {};
			std::vector<CModelRenderer*> m_modelRendererArray = {};
			std::list<nsFacility::IFacilityBase*> m_facilityList = {};
		};

	}
}