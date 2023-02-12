#pragma once
#include "WorldParts.h"

namespace nsAWA
{
	class CLoadGame;
	namespace nsHumans
	{
		class CHumanManager;
	}
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			class CMonsterPopManager;
		}
	}
}

namespace nsAWA
{
	namespace nsWorld
	{
		class CWorld : public IGameObject
		{
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

		private:
			void TryLoadLevel();

			void LoadLevel();

			void InitSkyCube();

			void UnexpectedLevelObject(const std::string& objName) const noexcept;

		private:
			CSkyCubeRenderer* m_skyCubeRenderer = nullptr;
			nsHumans::CHumanManager* m_humanManager = nullptr;
			nsMonster::nsMonsterPop::CMonsterPopManager* m_monsterPopManager = nullptr;

			bool m_isLevelLoaded = false;
			CWorldParts m_worldParts = {};
			TRSListMap m_levelTRS = {};
		};

	}
}