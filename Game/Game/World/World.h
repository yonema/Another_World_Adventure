#pragma once
#include "WorldParts.h"

namespace nsAWA
{
	class CLoadGame;
}

namespace nsAWA
{
	namespace nsWorld
	{
		class CWorld : public IGameObject
		{
		public:
			enum EnMode
			{
				enTutorial,
				enNormal,
				enNum
			};

		private:
			static const char* const m_kLevelFilePath;
			static const float m_kSkyCubeScale;

		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CWorld() = default;
			~CWorld() = default;

			constexpr bool IsLevelLoaded() const noexcept
			{
				return m_isLevelLoaded;
			}

			constexpr const auto& GetPlayerSpawnPosition() const noexcept
			{
				return m_playerSpawnPosition;
			}

			constexpr void SetMode(EnMode mode) noexcept
			{
				m_mode = mode;
			}

			constexpr auto GetMode() const noexcept
			{
				return m_mode;
			}

		private:
			void TryLoadLevel();

			void LoadLevel();

			void InitSkyCube();

			void UnexpectedLevelObject(const std::string& objName) const noexcept;

		private:
			CSkyCubeRenderer* m_skyCubeRenderer = nullptr;
			bool m_isLevelLoaded = false;
			CWorldParts m_worldParts = {};
			TRSListMap m_levelTRS = {};
			CVector3 m_playerSpawnPosition = CVector3::Zero();
			EnMode m_mode = EnMode::enNormal;
		};

	}
}