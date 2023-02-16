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

//���ɁB
#include "Monster/Monster.h"

namespace nsAWA {

	bool CLoadGame::Start()
	{

#ifdef _DEBUG
		//���C���[�t���[���������B
		SetCullingBoxForDebugDrawLine(100.0f, nsMath::CVector3::Zero());

		// ���C���̃J�����O�{�b�N�X�̎����J�����t�B�b�g�@�\�̗L�����B
		EnableAutoFitCullingBoxToMainCamera();
#endif

		//�Q�[�����X�g�𐶐��B
		CreateGameList();

		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
		m_player->SetPosition(m_playerSpawnPosition);
		m_player->SetRotation(m_playerSpawnQuaternion);

		//���C���J�����𐶐��B
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//�o�b�N�O���E���h�𐶐��B
		m_backGround = NewGO<nsBackGround::CBackGround>(nsBackGround::CBackGround::m_kObjName_BackGround);

		//BGM�Đ��B
		nsSound::CSoundManager::GetInstance()->ChangeBGM("MeadowBGM");


		return true;
	}

	void CLoadGame::Update(float deltaTime)
	{
		//�Q�[�����O���X�V�B
		nsGameLog::CGameLog::GetInstance()->Update(deltaTime);

#ifdef _DEBUG
		//�M�������o��������B
		if (Input()->IsTrigger(EnActionMapping::enUseItem)) {

			nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
		}
#endif
	}

	void CLoadGame::OnDestroy()
	{
		//�Q�[�����X�g��j���B
		DeleteGameList();

		//�v���C���[��j���B
		DeleteGO(m_player);

		//���C���J������j���B
		DeleteGO(m_mainCamera);

		//�n�`��j���B
		DeleteGO(m_backGround);
	}

	void CLoadGame::CreateGameList() {

		//�A�C�e�����X�g�𐶐��B
		nsItem::CAllItemList::GetInstance()->LoadAllItemList();

		//�f�ރA�C�e�����X�g�𐶐��B
		nsItem::CMaterialItemList::GetInstance()->LoadMaterialItemList();

		//�����X�^�[���X�g�𐶐��B
		nsMonster::CMonsterList::GetInstance()->CreateMonsterList();

		//�A�N�e�B�u�X�L���̃��X�g�𐶐��B
		//nsSkill::CActiveSkillList::GetInstance()->LoadActiveSkillList();

		//�p�b�V�u�X�L���̃��X�g�𐶐��B
		//nsSkill::CPassiveSkillList::GetInstance()->LoadPassiveSkillList();

		//����̃��X�g�𐶐��B
		nsWeapon::CWeaponList::GetInstance()->LoadWeaponList();

		//�h��̃��X�g�𐶐��B
		nsArmor::CArmorList::GetInstance()->LoadArmorList();

		//���@�̃��X�g�𐶐��B

		//nsMagic::CMagicList::GetInstance()->LoadMagicList();

		//�T�E���h�̃��X�g�𐶐��B
		nsSound::CSoundList::GetInstance()->LoadSoundList();
	}

	void CLoadGame::DeleteGameList() {

		//�A�C�e�����X�g��j���B
		nsItem::CAllItemList::GetInstance()->DeleteInstance();

		//�f�ރA�C�e�����X�g��j���B
		nsItem::CMaterialItemList::GetInstance()->DeleteInstance();

		//�����X�^�[���X�g��j���B
		nsMonster::CMonsterList::GetInstance()->DeleteInstance();

		//�A�N�e�B�u�X�L���̃��X�g��j���B
		nsSkill::CActiveSkillList::GetInstance()->DeleteInstance();

		//�p�b�V�u�X�L���̃��X�g��j���B
		nsSkill::CPassiveSkillList::GetInstance()->DeleteInstance();

		//����̃��X�g��j���B
		nsWeapon::CWeaponList::GetInstance()->DeleteInstance();

		//�h��̃��X�g��j���B
		nsArmor::CArmorList::GetInstance()->DeleteInstance();

		//���@�̃��X�g��j���B
		nsMagic::CMagicList::GetInstance()->DeleteInstance();

		//�T�E���h�̃��X�g��j���B
		nsSound::CSoundList::GetInstance()->DeleteInstance();

		//�T�E���h�Ǘ��N���X��j���B
		nsSound::CSoundManager::GetInstance()->DeleteInstance();
	}

	bool CLoadGame::IsPlayerInited() const noexcept
	{
		return m_player->IsInited();
	}





}