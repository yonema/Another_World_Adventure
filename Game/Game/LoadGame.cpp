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
#include "Item/MaterialItemList.h"
#include "GameLog/GameLog.h"
#include "Sound/SoundList.h"
#include "Sound/SoundManager.h"

//仮に。
#include "Monster/Monster.h"

namespace nsAWA {

	bool CLoadGame::Start()
	{

#ifdef _DEBUG
		//ワイヤーフレームを可視化。
		SetCullingBoxForDebugDrawLine(100.0f, nsMath::CVector3::Zero());

		// ラインのカリングボックスの自動カメラフィット機能の有効化。
		EnableAutoFitCullingBoxToMainCamera();
#endif

		//ゲームリストを生成。
		CreateGameList();

		//プレイヤーを生成。
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
		m_player->SetPosition(m_playerSpawnPosition);
		m_player->SetRotation(m_playerSpawnQuaternion);

		//メインカメラを生成。
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//バックグラウンドを生成。
		m_backGround = NewGO<nsBackGround::CBackGround>(nsBackGround::CBackGround::m_kObjName_BackGround);

		//BGM再生。
		nsSound::CSoundManager::GetInstance()->ChangeBGM("MeadowBGM");


		return true;
	}

	void CLoadGame::Update(float deltaTime)
	{
		//ゲームログを更新。
		nsGameLog::CGameLog::GetInstance()->Update(deltaTime);

#ifdef _DEBUG
		//ギヤラを出現させる。
		if (Input()->IsTrigger(EnActionMapping::enUseItem)) {

			nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
		}
#endif
	}

	void CLoadGame::OnDestroy()
	{
		//ゲームリストを破棄。
		DeleteGameList();

		//プレイヤーを破棄。
		DeleteGO(m_player);

		//メインカメラを破棄。
		DeleteGO(m_mainCamera);

		//地形を破棄。
		DeleteGO(m_backGround);
	}

	void CLoadGame::CreateGameList() {

		//アイテムリストを生成。
		nsItem::CAllItemList::GetInstance()->LoadAllItemList();

		//素材アイテムリストを生成。
		nsItem::CMaterialItemList::GetInstance()->LoadMaterialItemList();

		//モンスターリストを生成。
		nsMonster::CMonsterList::GetInstance()->CreateMonsterList();

		//アクティブスキルのリストを生成。
		//nsSkill::CActiveSkillList::GetInstance()->LoadActiveSkillList();

		//パッシブスキルのリストを生成。
		//nsSkill::CPassiveSkillList::GetInstance()->LoadPassiveSkillList();

		//武器のリストを生成。
		nsWeapon::CWeaponList::GetInstance()->LoadWeaponList();

		//防具のリストを生成。
		nsArmor::CArmorList::GetInstance()->LoadArmorList();

		//魔法のリストを生成。

		//nsMagic::CMagicList::GetInstance()->LoadMagicList();

		//サウンドのリストを生成。
		nsSound::CSoundList::GetInstance()->LoadSoundList();
	}

	void CLoadGame::DeleteGameList() {

		//アイテムリストを破棄。
		nsItem::CAllItemList::GetInstance()->DeleteInstance();

		//素材アイテムリストを破棄。
		nsItem::CMaterialItemList::GetInstance()->DeleteInstance();

		//モンスターリストを破棄。
		nsMonster::CMonsterList::GetInstance()->DeleteInstance();

		//アクティブスキルのリストを破棄。
		nsSkill::CActiveSkillList::GetInstance()->DeleteInstance();

		//パッシブスキルのリストを破棄。
		nsSkill::CPassiveSkillList::GetInstance()->DeleteInstance();

		//武器のリストを破棄。
		nsWeapon::CWeaponList::GetInstance()->DeleteInstance();

		//防具のリストを破棄。
		nsArmor::CArmorList::GetInstance()->DeleteInstance();

		//魔法のリストを破棄。
		nsMagic::CMagicList::GetInstance()->DeleteInstance();

		//サウンドのリストを破棄。
		nsSound::CSoundList::GetInstance()->DeleteInstance();

		//サウンド管理クラスを破棄。
		nsSound::CSoundManager::GetInstance()->DeleteInstance();
	}

	bool CLoadGame::IsPlayerInited() const noexcept
	{
		return m_player->IsInited();
	}





}