#pragma once
#include "FacilityBase.h"

namespace nsAWA
{
	namespace nsFacility
	{
		//建物のステート 他の建物でも使用できそうならIFacilityBaseに移したほうがいい?
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
			void InitBackgroundLevel();
		private:
			const std::string m_kSpritePath = "Assets/Images/ButtonRelated/Button_A.png";
			const CVector2 m_kSpriteSize = CVector2(300.0f,300.0f);
			const CVector2 m_kSpritePosition = CVector2(0.0f, -250.0f);
			const float m_kSpriteScale = 0.2f;
			const CVector4 m_kTransparent = CVector4(1.0f, 1.0f, 1.0f, 0.0f);

			const std::string m_kBackGroundLevelPath = "Assets/Level2D/LevelFiles/InnBackground.tdl";
		private:
			CSpriteRenderer* m_enterSprite = nullptr;

			CLevel2D m_backGroundLevel;

			EnFacilityState m_state = EnFacilityState::enClose;
		};

	}
}