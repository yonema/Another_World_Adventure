#pragma once
#include "MonsterPopInfo.h"
namespace nsAWA
{
	namespace nsMonster
	{
		class CMonster;

		namespace nsMonsterPop
		{
			class CMonsterPopManager;
		}
	}
}

namespace nsAWA
{
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			class CMonsterPopPoint : public IGameObject
			{
			private:
				static const float m_kMonsterPopDistance;
				static const float m_kMonsterPopMaxOffset;
				static const float m_kMonsterPopShiftPos;

				enum class EnGenerateState
				{
					enBeforeGenerate,
					enNowGenerating,
					enAfterGenerate,
				};

			public:
				bool Start() override final;

				void OnDestroy() override final;

				void Update(float deltaTime) override final;

			public:
				constexpr CMonsterPopPoint() = default;
				~CMonsterPopPoint() = default;

				static inline void SetPopManagerRef(CMonsterPopManager* popManagerRef)
				{
					m_popManagerRef = popManagerRef;
				}

				void Init(const MnsPopInfoList& popInfoListRef, const CVector3& pos);

			private:
				void UpdateCommon() noexcept;

				void UpdateBeforeGenerate() noexcept;

				void UpdateNowGenerating() noexcept;

				void UpdateAfterGenerate() noexcept;

				bool CheckPlayerFind() const noexcept;

				void GenerateMonster();

				void LostMonster() noexcept;

				void InitRandomParam() noexcept;

				void ChangeState(EnGenerateState newState);

			private:
				static CMonsterPopManager* m_popManagerRef;
				const MnsPopInfoList* m_popInfoListRef = nullptr;
				CVector3 m_position = CVector3::Zero();
				CVector3 m_randomPositionOffset = CVector3::Zero();
				int m_randomPopRate = 0;
				EnGenerateState m_generateState = EnGenerateState::enBeforeGenerate;
				std::vector<CMonster*> m_monsterArray = {};
				bool m_preIsPlayerInTown = false;
				bool m_isPlayerInTown = false;

				CPhysicsTriggerObject m_trigger = {};


			};

		}
	}
}