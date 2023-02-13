#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "Scenes/TitleScene.h"
#include "Network/NetworkManager.h"
#include "UI/Institution/Inn/InnWindowUI.h"



namespace nsAWA
{
	const char* const CGame::m_kGameObjectName = "Game";

	bool CGame::Start()
	{
		HandleApplicationArgument();

		nsScene::CreateScene<nsScene::CTitleScene>();


		return true;
	}

	void CGame::Update(float deltaTime)
	{
		return;
	}

	void CGame::OnDestroy()
	{
		nsScene::DeleteCurrentScene();

		return;
	}

	void CGame::HandleApplicationArgument()
	{
		//�R�}���h���C���������擾
		std::string argumentLine = GetCommandLineA();
		
		//�v���C���[���ƍ����t����쐬�����n�b�V���R�[�h
		std::string hashCode = "";

		//�l�b�g���[�N�̐ڑ����
		std::string networkMode = "";

		//�R�}���h���C��������' '�ŋ�؂��Ă���̂ł܂�2����
		auto firstSplit = nsUtils::SplitString(argumentLine.c_str(),' ');

		//�R�}���h���C��������������Ȃ���΃G���[�B
		if (firstSplit.second.length() <= 0)
		{
#ifdef _DEBUG
	
			hashCode = "ERROR_ARGUMENT_NOT_FOUND";

			networkMode = "NETWORK_OFFLINE";

#else

			nsGameWindow::MessageBoxWarning(L"�G���[�B�����`���[����Q�[�����N�����ĉ������B");

			std::exit(EXIT_FAILURE);

#endif
		}
		else
		{
			//�R�}���h���C��������2�ȏ゠��΁A�l���擾����
			auto gameArguments = nsUtils::SplitString(firstSplit.second.c_str(), ' ');

			hashCode = gameArguments.first;

			networkMode = gameArguments.second;
		}

		//�l�b�g���[�N�C���X�^���X���쐬���A�n�b�V���R�[�h��o�^
		nsNetwork::CNetworkManager::CreateInstance(networkMode)->SetHashCode(hashCode);
	}
}
