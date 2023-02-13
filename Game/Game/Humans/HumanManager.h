#pragma once
#include "HumanAnimationType.h"

namespace nsAWA
{
	namespace nsHumans
	{
		class CHuman;
		class CTalkToPlayer;
	}
	namespace nsPlayer 
	{
		class CPlayer;
	}
}
namespace nsAWA
{
	namespace nsHumans
	{
		class CHumanManager : public IGameObject
		{
		public:
			static const char* const m_kRetargetSkeltonName;
			static const char* const m_kHumanPrefix;

		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CHumanManager() = default;
			~CHumanManager() = default;

			void GenerateBase(bool loadingAsynchronous = false);

			void GenerateHuman(
				const std::string& objName, const CVector3& position, const CQuaternion& rotation);

			void Release();

			constexpr auto GetBaseLoadingState() const noexcept
			{
				return m_baseLoadingState;
			}

			constexpr bool IsBaseLoaded() const noexcept
			{
				return GetBaseLoadingState() == EnLoadingState::enAfterLoading;
			}

			constexpr void SetPlayerRef(const nsPlayer::CPlayer* playerRef) noexcept
			{
				m_playerRef = playerRef;
			}

			constexpr const auto* GetPlayerRef() const noexcept
			{
				return m_playerRef;
			}

			constexpr const auto& GetHumanMap() const noexcept
			{
				return m_humanMap;
			}

			void ActivateAllHumans();

			void DeactivateAllHumans();

			constexpr bool IsPlayerInTown() const noexcept
			{
				return m_isPlayerInTown;
			}

		private:
			void CheckBaseHumanLoading() noexcept;

		private:
			std::unordered_map<std::string, CHuman*> m_humanMap = {};
			EnLoadingState m_baseLoadingState = EnLoadingState::enBeforeLoading;
			CModelRenderer* m_baseHumanMR = nullptr;
			const nsPlayer::CPlayer* m_playerRef = nullptr;
			CTalkToPlayer* m_talkToPlayer = nullptr;
			bool m_isPlayerInTown = false;
		};

	}
}