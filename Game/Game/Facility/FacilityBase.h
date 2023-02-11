#pragma once
namespace nsAWA
{
	namespace nsFacility
	{
		class IFacilityBase : public IGameObject
		{
		public:
			virtual void OnTriggerEnter(CExtendedDataForRigidActor* otherData) {};
			virtual void OnTriggerStay(CExtendedDataForRigidActor* otherData) {};
			virtual void OnTriggerExit(CExtendedDataForRigidActor* otherData) {};

		public:
			constexpr IFacilityBase() = default;
			~IFacilityBase();

			bool Init(
				const CVector3& position,
				const CQuaternion& rotation,
				const CVector3& scale,
				const char* collisionModelFilePath,
				EnPhysicsAttributes attribute = EnPhysicsAttributes::enNone
			);

		private:
			void Terminate();

		private:
			CPhysicsTriggerObject m_trigger = {};
		};

	}
}