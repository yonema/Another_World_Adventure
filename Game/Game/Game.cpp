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
		//�v���C���[�𐶐��B
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//���C���J�����𐶐��B
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

#ifdef _DEBUG

		//�A�C�e�����������B
		nsItem::CItem item;
		item.Create();
#endif

#ifdef _DEBUG
		//csv�ǂݍ��݂��܂��ł��Ȃ����߁A�蓮�Őݒ�B
		//nsMonster::SMonsterInfo monsterInfo;
		//monsterInfo.name = "Giyara";
		//monsterInfo.modelFilePath = "Assets/Models/Giyara.fbx";
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
