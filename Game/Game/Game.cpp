#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "../YonemaEngine.h"
#include "Player/Player.h"
#include "Camera/MainCamera.h"
#include "BackGround/BackGround.h"
#include "Item/AllItemList.h"
#include "Monster/MonsterList.h"
#include "Skill/ActiveSkillList.h"

#ifdef _DEBUG
#include "Monster/Monster.h"
#include "Monster/MonsterList.h"
#include "Item/SelfItem.h"
#include "Feature/AbnormalStatus/Poison.h"
#include "Item/ItemManager.h"
#include "Monster/AI/MonsterAIController.h"
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

		// ラインのカリングボックスの自動カメラフィット機能の有効化。
		EnableAutoFitCullingBoxToMainCamera();
#endif

		//プレイヤーを生成。
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//メインカメラを生成。
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//バックグラウンドを生成。
		m_backGround = NewGO<nsBackGround::CBackGround>(nsBackGround::CBackGround::m_kObjName_BackGround);

		//アイテムリストを生成。
		nsItem::CAllItemList::GetInstance()->LoadAllItemList();

		//モンスターリストを生成。
		nsMonster::CMonsterList::GetInstance()->CreateMonsterList();

		//アクティブスキルのリストを生成。
		nsSkill::CActiveSkillList::GetInstance()->LoadActiveSkillList();

#ifdef _DEBUG
		nsMonster::CMonster* monster = nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
		monster->SetPosition({ 0.0f,0.0f,100.0f });
#endif
		return true;
	}

	void CGame::Update(float deltaTime)
	{

//#ifdef _DEBUG
//		//ギヤラを出現させる。
//		if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {
//
//			nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
//		}
//#endif
	}

	void CGame::OnDestroy()
	{
		//プレイヤーを破棄。
		DeleteGO(m_player);

		//メインカメラを破棄。
		DeleteGO(m_mainCamera);
	}
}
