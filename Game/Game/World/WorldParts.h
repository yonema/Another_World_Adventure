#pragma once
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
			struct STRS
			{
				constexpr STRS() = default;
				STRS(const CVector3& pos, const CQuaternion& rot, const CVector3& scale)
					:pos(pos), rot(rot), scale(scale)
				{};
				~STRS() = default;


				CMatrix CalcMatrix() const noexcept
				{
					CMatrix mTrans, mRot, mScale;
					mTrans.MakeTranslation(pos);
					mRot.MakeRotationFromQuaternion(rot);
					mScale.MakeScaling(scale);

					return mScale * mRot * mTrans;
				}

				CVector3 pos;
				CQuaternion rot;
				CVector3 scale;
			};

			using TRSList = std::list<STRS>;
			using TRSMap = std::unordered_map<std::string, STRS>;
			using TRSListMap = std::unordered_map<std::string, TRSList>;

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