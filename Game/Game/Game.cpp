#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "../YonemaEngine.h"
#include "Player/Player.h"
#include "Camera/MainCamera.h"
#include "BackGround/BackGround.h"
#include "Item/AllItemList.h"

#ifdef _DEBUG
#include "Monster/Monster.h"
#include "Monster/MonsterList.h"
#include "Item/SelfItem.h"
#include "Feature/AbnormalStatus/Poison.h"
#include "Item/ItemManager.h"
#endif

namespace nsAWA
{
	const char* const CGame::m_kGameObjectName = "Game";

	bool CGame::Start()
	{
#ifdef _DEBUG
		//ワイヤーフレームを可視化。
		EnableDebugDrawPhysicsLine();
		SetCullingBoxForDebugDrawLine(100.0f, nsMath::CVector3::Zero());
#endif

		//プレイヤーを生成。
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//メインカメラを生成。
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//バックグラウンドを生成。
		m_backGround = NewGO<nsBackGround::CBackGround>(nsBackGround::CBackGround::m_kObjName_BackGround);

		//アイテムリストを生成。
		nsItem::CAllItemList::GetInstance()->LoadAllItemList();

#ifdef _DEBUG
		////csv読み込みがまだできないため、手動で設定。
		//nsMonster::SMonsterInfo monsterInfo;
		//monsterInfo.name = "Giyara";
		//monsterInfo.modelFilePath = "Assets/Models/Giyara.fbx";
		//monsterInfo.monster = nsMonster::EnMonsterList::enGiyara;
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
