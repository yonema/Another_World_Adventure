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
	}
}