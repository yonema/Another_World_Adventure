#include "YonemaEnginePreCompile.h"
#include "NetworkManager.h"
#include <cpprest/http_client.h>
#include <Sensapi.h>
#include <fstream>

using namespace web;                        // URIのような共通の機能
using namespace web::http;                  // 共通のHTTP機能
using namespace web::http::client;          // HTTP クライアントの機能

namespace nsAWA
{
	namespace nsNetwork
	{
		CNetworkManager* CNetworkManager::m_instance = nullptr;

		void CNetworkManager::UploadSaveData()
		{
			//ネットワークモードを調べる
			if (m_networkMode != "NETWORK_ONLINE")
			{
				return;
			}

			//現在のネットワーク状況を調べる
			if (IsNetworkAccessible() == false)
			{
				m_networkMode = "NETWORK_OFFLINE";

				return;
			}

			std::string saveData = LoadLocalSaveData();

			if (saveData == "")
			{
				return;
			}

			std::string eventSaveData = LoadLocalEventSaveData();

			if (eventSaveData == "")
			{
				return;
			}

			//int a = std::string::max_size();

			std::string uploadData;
			uploadData.reserve(static_cast<size_t>(1000));
			uploadData = saveData;
			uploadData += "*eventData*";
			uploadData += eventSaveData;

			//アップロード処理
			HttpUpload(uploadData);

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

			m_serverURL = nsUtils::GetWideStringFromString(url.c_str());

			fclose(fp);

		}

		bool CNetworkManager::IsNetworkAccessible()
		{
			BOOL isAlive;
			DWORD networkFlag;
			DWORD error;


			isAlive = IsNetworkAlive(&networkFlag);
			error = GetLastError();

			if (error == 0 && isAlive == TRUE)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		std::string CNetworkManager::LoadLocalSaveData()
		{
			std::ifstream ifs(m_kSaveDataPath);

			//オープンに失敗したら無を返す
			if (!ifs)
			{
				return "";
			}

			std::string saveDataStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

			return saveDataStr;
		}
		
		std::string CNetworkManager::LoadLocalEventSaveData()
		{
			std::ifstream ifs(m_kEventSaveDataPath);

			//オープンに失敗したら無を返す
			if (!ifs)
			{
				return "";
			}

			std::string saveDataStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

			return saveDataStr;
		}

		void CNetworkManager::HttpUpload(const std::string& saveData)
		{
			pplx::create_task([=]
				{
					// クライアントの設定
					http_client client(m_serverURL);

					// 送信データの作成
					json::value postData;

					std::wstring wSaveData = nsUtils::GetWideStringFromString(saveData.c_str());
					postData[L"saveDataCSV"] = json::value::string(wSaveData.c_str());

					// リクエスト送信
					return client.request(methods::PATCH, L"playerData/" + m_hashCode, postData.serialize(), L"application/json");
				})
			.then([](http_response  response)
				{
					// ステータスコード判定
					if (response.status_code() != status_codes::OK)
					{
						//アップロードエラー。ただゲーム側には特に影響しない。
						nsGameWindow::MessageBoxError(L"セーブデータのアップロードに失敗しました。");
					}
				});
		}
	}
}