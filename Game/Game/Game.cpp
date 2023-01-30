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
		//���C���[�t���[���������B
		EnableDebugDrawPhysicsLine();
		SetCullingBoxForDebugDrawLine(100.0f, nsMath::CVector3::Zero());

		// ���C���̃J�����O�{�b�N�X�̎����J�����t�B�b�g�@�\�̗L�����B
		EnableAutoFitCullingBoxToMainCamera();
#endif

		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//���C���J�����𐶐��B
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//�o�b�N�O���E���h�𐶐��B
		m_backGround = NewGO<nsBackGround::CBackGround>(nsBackGround::CBackGround::m_kObjName_BackGround);

		//�A�C�e�����X�g�𐶐��B
		nsItem::CAllItemList::GetInstance()->LoadAllItemList();

		//�����X�^�[���X�g�𐶐��B
		nsMonster::CMonsterList::GetInstance()->CreateMonsterList();

		//�A�N�e�B�u�X�L���̃��X�g�𐶐��B
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
//		//�M�������o��������B
//		if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {
//
//			nsMonster::CMonsterList::GetInstance()->CreateMonster("Giyara");
//		}
//#endif
	}

	void CGame::OnDestroy()
	{
		//�v���C���[��j���B
		DeleteGO(m_player);

		//���C���J������j���B
		DeleteGO(m_mainCamera);
	}
}
