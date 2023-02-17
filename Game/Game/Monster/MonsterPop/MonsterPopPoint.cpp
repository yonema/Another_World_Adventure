#include "MonsterPopPoint.h"
#include "MonsterPopManager.h"
#include "../../Humans/HumanManager.h"
#include "../../Player/Player.h"
#include "../Monster.h"
#include "../MonsterList.h"
#include "../../../YonemaEngine/EngineConfig.h"

namespace nsAWA
{
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			CMonsterPopManager* CMonsterPopPoint::m_popManagerRef = nullptr;
			const float CMonsterPopPoint::m_kMonsterPopDistance = 500.0f;
			const float CMonsterPopPoint::m_kMonsterPopMaxOffset = 50.0f;
			const float CMonsterPopPoint::m_kMonsterPopShiftPos = 10.0f;

			const std::unordered_map<std::string, const char* const>
				CMonsterPopPoint::m_popNameToCreateName =
			{
				{"ギヤラ", "Giyara"},
				{"スケルトン", "Skeleton"},
				{"イーグル", "Eagle"},
			};


			bool CMonsterPopPoint::Start()
			{

				return true;
			}

			void CMonsterPopPoint::OnDestroy()
			{
				for (auto& monster : m_monsterArray)
				{
					if (monster == nullptr)
					{
						continue;
					}
					DeleteGO(monster);
					monster = nullptr;
				}
				m_monsterArray.clear();

#ifdef DRAW_COLLISION
				m_trigger.Release();
#endif // DRAW_COLLISION

				return;
			}

			void CMonsterPopPoint::Update(float deltaTime)
			{
				UpdateCommon();

				switch (m_generateState)
				{
				case EnGenerateState::enBeforeGenerate:
					UpdateBeforeGenerate();
					break;
				case EnGenerateState::enNowGenerating:
					UpdateNowGenerating();
					break;
				case EnGenerateState::enAfterGenerate:
					UpdateAfterGenerate();
					break;
				}



				return;
			}


			void CMonsterPopPoint::Init(
				const MnsPopInfoList& popInfoListRef, const CVector3& pos)
			{
				m_popInfoListRef = &popInfoListRef;

				m_position = pos;

				InitRandomParam();

#ifdef _DEBUG
				m_trigger.InitAsSphere(m_kMonsterPopDistance, m_position);
#endif // _DEBUG


				return;
			}

			void CMonsterPopPoint::UpdateCommon() noexcept
			{
				const auto* humanManager = m_popManagerRef->GetHumanManagerRef();

				if (humanManager == nullptr)
				{
					m_isPlayerInTown = true;
					return;
				}

				if (humanManager->IsPlayerInTown())
				{
					m_isPlayerInTown = true;
				}
				else
				{
					m_isPlayerInTown = false;
				}

				if (m_isPlayerInTown)
				{
					if (m_preIsPlayerInTown != true)
					{
						InitRandomParam();
					}
					m_preIsPlayerInTown = true;
					return;
				}
				else
				{
					m_preIsPlayerInTown = false;
				}

				return;
			}

			void CMonsterPopPoint::UpdateBeforeGenerate() noexcept
			{
				if (m_isPlayerInTown)
				{
					return;
				}

				const auto* playerRef = m_popManagerRef->GetHumanManagerRef()->GetPlayerRef();
				if (playerRef == nullptr)
				{
					return;
				}

				auto dist = playerRef->GetPosition() - m_position;

				if (dist.Length() < m_kMonsterPopDistance)
				{
					ChangeState(EnGenerateState::enNowGenerating);
				}

				return;
			}

			void CMonsterPopPoint::UpdateNowGenerating() noexcept
			{
				bool allDeath = true;
				for (auto& monster : m_monsterArray)
				{
					if (monster == nullptr)
					{
						continue;
					}
					if (monster->IsDeath())
					{
						monster = nullptr;
					}
					else
					{
						allDeath = false;
					}
				}

				if (allDeath)
				{
					ChangeState(EnGenerateState::enAfterGenerate);
					return;
				}

				if (m_isPlayerInTown)
				{
					LostMonster();
					return;
				}

				const auto& playerPos =
					m_popManagerRef->GetHumanManagerRef()->GetPlayerRef()->GetPosition();
				auto dist = playerPos - m_position;

				if (dist.Length() > m_kMonsterPopDistance)
				{
					LostMonster();
					return;
				}

				return;
			}

			void CMonsterPopPoint::UpdateAfterGenerate() noexcept
			{
				if (m_isPlayerInTown)
				{
					ChangeState(EnGenerateState::enBeforeGenerate);
					return;
				}

				return;
			}

			bool CMonsterPopPoint::CheckPlayerFind() const noexcept
			{
				const auto* humanManager = m_popManagerRef->GetHumanManagerRef();
				if (humanManager == nullptr)
				{
					return false;
				}

				if (humanManager->IsPlayerInTown())
				{
					return false;
				}

				const auto* playerRef = humanManager->GetPlayerRef();
				if (playerRef == nullptr)
				{
					return false;
				}


				return true;
			}

			void CMonsterPopPoint::GenerateMonster()
			{
				int popRateSum = 0;
				const SMonsterPopInfo* popInfoRef = nullptr;
				for (const auto& popInfo : *m_popInfoListRef)
				{
					popRateSum += popInfo.popRate;

					if (m_randomPopRate <= popRateSum)
					{
						popInfoRef = &popInfo;
						break;
					}
				}

				if (popInfoRef == nullptr)
				{
					return;
				}

				m_monsterArray.reserve(popInfoRef->nameArray.size());
				auto popPos = m_position;
				for (const auto& name : popInfoRef->nameArray)
				{
					const auto& monsterName = name;
					auto itr = m_popNameToCreateName.find(monsterName);
					const char* createName = nullptr;
					if (itr == m_popNameToCreateName.end())
					{
						createName = "Giyara";
					}
					else
					{
						createName = itr->second;
					}
					auto* monster = nsMonster::CMonsterList::GetInstance()->CreateMonster(createName);
					monster->SetPosition(popPos);
					popPos.x += m_kMonsterPopShiftPos;

					m_monsterArray.emplace_back(monster);
				}


				return;
			}

			void CMonsterPopPoint::LostMonster() noexcept
			{
				for (auto& monster : m_monsterArray)
				{
					if (monster == nullptr)
					{
						continue;
					}

					DeleteGO(monster);
					monster = nullptr;
				}
				m_monsterArray.clear();

				ChangeState(EnGenerateState::enBeforeGenerate);

				return;
			}


			void CMonsterPopPoint::InitRandomParam() noexcept
			{
				m_randomPositionOffset.x = Random()->GetRangeFloat(0.0f, m_kMonsterPopMaxOffset);
				m_randomPositionOffset.z = Random()->GetRangeFloat(0.0f, m_kMonsterPopMaxOffset);

				m_randomPopRate = Random()->GetRangeInt(1, 100);

				return;
			}



			void CMonsterPopPoint::ChangeState(EnGenerateState newState)
			{
				if (m_generateState == newState)
				{
					return;
				}

				m_generateState = newState;

				switch (m_generateState)
				{
				case EnGenerateState::enBeforeGenerate:
					break;
				case EnGenerateState::enNowGenerating:
					GenerateMonster();
					break;
				case EnGenerateState::enAfterGenerate:
					break;
				default:
					break;
				}


				return;
			}




		}
	}
}