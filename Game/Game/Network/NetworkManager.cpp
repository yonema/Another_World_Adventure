#include "YonemaEnginePreCompile.h"
#include "NetworkManager.h"
#include <cpprest/http_client.h>

namespace nsAWA
{
	namespace nsNetwork
	{
		CNetworkManager* CNetworkManager::m_instance = nullptr;

		void CNetworkManager::UploadSaveData()
		{
			if (m_networkMode == "NETWORK_OFFLINE")
			{
				return;
			}

			//アップロード処理

		}

		void CNetworkManager::GetURL()
		{
			FILE* fp = nullptr;
			fopen_s(&fp, m_kNetworkSettingPath.c_str(), "rb");

			if (fp == nullptr)
			{
				//ファイルが見つからない。
				nsGameWindow::MessageBoxWarning(L"ネットワークの設定ファイルが見つかりません。");
				m_networkMode = "NETWORK_OFFLINE";
				return;
			}

			//URLの長さ取得
			int URLLen = 0;
			fread(&URLLen, sizeof(int), 1, fp);

			std::string url = "";

			for (int i = 0;i < URLLen;i++)
			{
				//URLを復号
				//複合キーも直接書いてるけどURLをベタ書きでGitHubにあげるよりかは幾分かマシ。
				char letter = '\0';
				fread(&letter, sizeof(char), 1, fp);

				url += letter ^ m_kURLKey[i];
			}

			m_serverURL = url;

			fclose(fp);

		}
	}
}