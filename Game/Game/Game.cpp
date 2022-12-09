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
		//���C���[�t���[���������B
		EnableDebugDrawPhysicsLine();
		SetCullingBoxForDebugDrawLine(100.0f, nsMath::CVector3::Zero());
#endif

		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//���C���J�����𐶐��B
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//�o�b�N�O���E���h�𐶐��B
		m_backGround = NewGO<nsBackGround::CBackGround>(nsBackGround::CBackGround::m_kObjName_BackGround);

		//�A�C�e�����X�g�𐶐��B
		nsItem::CAllItemList::GetInstance()->LoadAllItemList();

#ifdef _DEBUG
		////csv�ǂݍ��݂��܂��ł��Ȃ����߁A�蓮�Őݒ�B
		//nsMonster::SMonsterInfo monsterInfo;
		//monsterInfo.name = "Giyara";
		//monsterInfo.modelFilePath = "Assets/Models/Giyara.fbx";
		//monsterInfo.monster = nsMonster::EnMonsterList::enGiyara;
		//
		////�������Ƀ����X�^�[���f���𐶐��B
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
		//�v���C���[��j���B
		DeleteGO(m_player);

		//���C���J������j���B
		DeleteGO(m_mainCamera);
	}
}
