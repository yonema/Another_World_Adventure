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
		//コマンドライン引数を取得
		std::string argumentLine = GetCommandLineA();
		
		//プレイヤー名と合言葉から作成したハッシュコード
		std::string hashCode = "";

		//ネットワークの接続状態
		std::string networkMode = "";

		//コマンドライン引数は' 'で区切られているのでまず2分割
		auto firstSplit = nsUtils::SplitString(argumentLine.c_str(),' ');

		//コマンドライン引数が一つしかなければエラー。
		if (firstSplit.second.length() <= 0)
		{
#ifdef _DEBUG
	
			hashCode = "ERROR_ARGUMENT_NOT_FOUND";

			networkMode = "NETWORK_OFFLINE";

#else

			nsGameWindow::MessageBoxWarning(L"エラー。ランチャーからゲームを起動して下さい。");

			std::exit(EXIT_FAILURE);

#endif
		}
		else
		{
			//コマンドライン引数が2個以上あれば、値を取得する
			auto gameArguments = nsUtils::SplitString(firstSplit.second.c_str(), ' ');

			hashCode = gameArguments.first;

			networkMode = gameArguments.second;
		}

		//ネットワークインスタンスを作成し、ハッシュコードを登録
		nsNetwork::CNetworkManager::CreateInstance(networkMode)->SetHashCode(hashCode);
	}
}
