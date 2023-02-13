#include "World.h"
#include "../Humans/HumanManager.h"
#include "../Monster/MonsterPop/MonsterPopManager.h"
#include "../EngineConfig.h"

namespace nsAWA
{
	namespace nsWorld
	{
		const char* const CWorld::m_kLevelFilePath = "Assets/Level3D/WorldLevel.fbx";
		const float CWorld::m_kSkyCubeScale = 5000.0f;

		bool CWorld::Start()
		{
#ifdef DRAW_COLLISION
			SetCullingBoxForDebugDrawLine(500.0f, nsMath::CVector3::Zero());

			// ラインのカリングボックスの自動カメラフィット機能の有効化。
			EnableAutoFitCullingBoxToMainCamera();
#endif // DRAW_COLLISION

			m_humanManager = NewGO<nsHumans::CHumanManager>("HumanManager");
			m_humanManager->GenerateBase(true);

			m_monsterPopManager = 
				NewGO<nsMonster::nsMonsterPop::CMonsterPopManager>("MonsterPopManager");
			m_monsterPopManager->SetHumanManagerRef(*m_humanManager);

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
			m_humanManager->Release();
			DeleteGO(m_humanManager);
			m_humanManager = nullptr;

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

			if (m_humanManager->IsBaseLoaded() != true)
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
						m_humanManager->GenerateHuman(
							chipData.name, chipData.position, chipData.rotation);
						return true;
					}
					else if (chipData.EqualObjectName("PlayerSpawn"))
					{
						return true;
					}
					else if (chipData.ForwardMatchName(
						nsMonster::nsMonsterPop::CMonsterPopManager::m_kMonsterPopPrefix))
					{
						m_monsterPopManager->GenerateMonsterPopPoint(
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

			m_worldParts.Build(m_humanManager);

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