#pragma once
#include "HumanModelRenderer.h"
namespace nsAWA
{
	namespace nsHumans
	{
		class CHumanManager;
	}
}

namespace nsAWA
{
	namespace nsHumans
	{
		class CHuman : public IGameObject
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CHuman() = default;
			~CHuman() = default;

			void Init(
				const char* name,
				const CVector3& position,
				const CQuaternion& rotation, 
				const char* filePath
			);

			void Release();

			constexpr const auto* GetHumanModelRenderer() const noexcept
			{
				return m_humanMR;
			}

			constexpr bool IsValid() const noexcept
			{
				return GetHumanModelRenderer();
			}

			constexpr const auto& GetPosition() const noexcept
			{
				return IsValid() ? GetHumanModelRenderer()->GetPosition() : CVector3::Zero();
			}

			constexpr const auto& GetRotation() const noexcept
			{
				return IsValid() ? GetHumanModelRenderer()->GetRotation() : CQuaternion::Identity();
			}

			constexpr const auto& GetName() const noexcept
			{
				return m_name;
			}

			constexpr bool IsLoaded() const noexcept
			{
				return IsValid() ? GetHumanModelRenderer()->IsLoaded() : false;
			}
			
			constexpr bool GetEnableTalking() const noexcept
			{
				return m_enableTalking;
			}

			constexpr void HumanActivate() noexcept
			{
				if (m_humanMR)
				{
					m_humanMR->ModelActivate();
				}
			}

			constexpr void HumanDeactivate() noexcept
			{
				if (m_humanMR)
				{
					m_humanMR->ModelDeactivate();
				}
			}


			static void SetHumanaManager(CHumanManager* manager) noexcept
			{
				m_humanManager = manager;
			}

		private:

			void CheckEnableTalking();

			void ChangeLoadingState(EnLoadingState newState);

		private:
			static CHumanManager* m_humanManager;
			CHumanModelRenderer* m_humanMR = nullptr;
			std::string m_name = {};
			bool m_enableTalking = false;
			EnLoadingState m_loadingState = EnLoadingState::enBeforeLoading;
		};

	}
}
