#include "World.h"
#include "../GamePreLoading.h"
#include "../Event/EventManager.h"
#include "../Humans/HumanManager.h"
#include "../Humans/Human.h"
#include "../Monster/MonsterPop/MonsterPopManager.h"

namespace nsAWA
{
	namespace nsWorld
	{
		const char* const CWorld::m_kLevelFilePath = "Assets/Level3D/WorldLevel.fbx";
		const float CWorld::m_kSkyCubeScale = 5000.0f;

		bool CWorld::Start()
		{
			InitSkyCube();

			return true;
		}

		void CWorld::Update(float deltaTime)
		{
			TryLoadLevel();

			return;
		}

		void CWorld::OnDestroy()
		{
			DeleteGO(m_skyCubeRenderer);
			m_skyCubeRenderer = nullptr;

			return;
		}

		void CWorld::TryLoadLevel()
		{
			if (m_isLevelLoaded)
			{
				return;
			}

			LoadLevel();

			return;
		}


		void CWorld::LoadLevel()
		{

			CLevel3D level3D;

			level3D.Init(
				m_kLevelFilePath,
				[&](const SLevelChipData& chipData)->bool
				{
					if (chipData.ForwardMatchName(nsHumans::CHumanManager::m_kHumanPrefix))
					{
						CGamePreLoading::GetInstance()->GetHumanManager()->
							GenerateHuman(
							chipData.name, chipData.position, chipData.rotation);
						return true;
					}
					else if (chipData.ForwardMatchName("PlayerSpawn_"))
					{
						const char* sarchName = chipData.name.c_str();

						sarchName += strlen("PlayerSpawn_");

						const char* nameByMode = "Town";
						if (m_mode == EnMode::enTutorial)
						{
							nameByMode = "Tutorial";
						}

						if (nsUtils::ForwardMatchName(sarchName, nameByMode))
						{
							m_playerSpawnPosition = chipData.position;
							CQuaternion rot;
							rot.SetRotationXDeg(-90.0f);
							m_playerSpawnRotation = chipData.rotation * rot;
						}

						return true;
					}
					else if (chipData.ForwardMatchName(
						nsMonster::nsMonsterPop::CMonsterPopManager::m_kMonsterPopPrefix))
					{
						CGamePreLoading::GetInstance()->GetMonsterPopManager()->
							GenerateMonsterPopPoint(
							chipData.name, chipData.position);
						return true;
					}
					else
					{
						bool res = m_worldParts.PushWorldData(
							chipData.name, chipData.position, chipData.rotation, chipData.scale);

						if (res != true)
						{
							UnexpectedLevelObject(chipData.name);
						}

						return true;
					}

					UnexpectedLevelObject(chipData.name);

					return true;
				}
			);

			m_worldParts.Build(CGamePreLoading::GetInstance()->GetHumanManager());

			m_isLevelLoaded = true;

			return;
		}

		void CWorld::InitSkyCube()
		{
			m_skyCubeRenderer = NewGO<CSkyCubeRenderer>();
			m_skyCubeRenderer->Init(EnSkyType::enNormal);
			m_skyCubeRenderer->SetScale(m_kSkyCubeScale);
			m_skyCubeRenderer->SetAutoFollowCameraFlag(true);
			m_skyCubeRenderer->SetAutoRotateFlag(true);

			return;
		}

		void CWorld::UnexpectedLevelObject(const std::string& objName) const noexcept
		{
			std::wstring wstr = L"予想外のオブジェクト ";
			wstr += nsUtils::GetWideStringFromString(objName);
			wstr.erase(wstr.end() - 1);
			wstr += L" がレベルで読み込まれています。";
			nsGameWindow::MessageBoxWarning(wstr.c_str());

			return;
		}


	}
}