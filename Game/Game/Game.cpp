#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "../YonemaEngine.h"
#include "Player/Player.h"
#include "Camera/MainCamera.h"
#include "Monster/Monster.h"
#include "Item/Item.h"

namespace nsAWA
{
	const char* const CGame::m_kGameObjectName = "Game";

	bool CGame::Start()
	{
		//プレイヤーを生成。
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//メインカメラを生成。
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

#ifdef _DEBUG

		//アイテムを仮生成。
		nsItem::CItem item;
		item.Create();
#endif

#ifdef _DEBUG
		//csv読み込みがまだできないため、手動で設定。
		//nsMonster::SMonsterInfo monsterInfo;
		//monsterInfo.name = "Giyara";
		//monsterInfo.modelFilePath = "Assets/Models/Giyara.fbx";
		//
		////情報を元にモンスターモデルを生成。
		//auto monster = NewGO<nsMonster::CMonster>(nsMonster::CMonster::m_kObjName_Monster);
		//monster->Create(monsterInfo);
#endif

		return true;
	}

	void CGame::Update(float deltaTime)
	{
		
	}

	void CGame::OnDestroy()
	{
		//プレイヤーを破棄。
		DeleteGO(m_player);

		//メインカメラを破棄。
		DeleteGO(m_mainCamera);
	}
}
