#include "YonemaEnginePreCompile.h"
#include "LoadGame.h"
#include "../YonemaEngine.h"
#include "Player/Player.h"
#include "Camera/MainCamera.h"
#include "BackGround/BackGround.h"
#include "Item/AllItemList.h"
#include "Monster/MonsterList.h"
#include "Skill/ActiveSkillList.h"
#include "Skill/PassiveSkillList.h"
#include "Weapon/WeaponList.h"
#include "Armor/ArmorList.h"
#include "Magic/MagicList.h"

#ifdef _DEBUG
#include "Monster/Monster.h"
#include "Monster/MonsterList.h"
#include "Item/SelfItem.h"
#include "Feature/AbnormalStatus/Poison.h"
#include "Item/ItemManager.h"
#include "Monster/AI/MonsterAIController.h"
#endif

namespace nsAWA {

	bool CLoadGame::Start()
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

		//パッシブスキルのリストを生成。
		nsSkill::CPassiveSkillList::GetInstance()->LoadPassiveSkillList();

		//武器のリストを生成。
		nsWeapon::CWeaponList::GetInstance()->LoadWeaponList();

		//防具のリストを生成。
		nsArmor::CArmorList::GetInstance()->LoadArmorList();

		//魔法のリストを生成。
		nsMagic::CMagicList::GetInstance()->LoadMagicList();

#ifdef _DEBUG
		nsMonster::CMonster* monster = nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
		monster->SetPosition({ 0.0f,0.0f,50.0f });
#endif
		return true;
	}

	void CLoadGame::Update(float deltaTime)
	{
#ifdef _DEBUG
		//ギヤラを出現させる。
		if (Input()->IsTrigger(EnActionMapping::enUseItem)) {

			nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
		}
#endif
	}

	void CLoadGame::OnDestroy()
	{
		//プレイヤーを破棄。
		DeleteGO(m_player);

		//メインカメラを破棄。
		DeleteGO(m_mainCamera);
	}
}