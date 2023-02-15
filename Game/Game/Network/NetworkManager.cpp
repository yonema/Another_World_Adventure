#include "YonemaEnginePreCompile.h"
#include "NetworkManager.h"
#include <cpprest/http_client.h>
#include <Sensapi.h>
#include <fstream>

using namespace web;                        // URI�̂悤�ȋ��ʂ̋@�\
using namespace web::http;                  // ���ʂ�HTTP�@�\
using namespace web::http::client;          // HTTP �N���C�A���g�̋@�\

namespace nsAWA
{
	namespace nsNetwork
	{
		CNetworkManager* CNetworkManager::m_instance = nullptr;

		void CNetworkManager::UploadSaveData()
		{
			//�l�b�g���[�N���[�h�𒲂ׂ�
			if (m_networkMode != "NETWORK_ONLINE")
			{
				return;
			}

			//���݂̃l�b�g���[�N�󋵂𒲂ׂ�
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

			//�A�b�v���[�h����
			HttpUpload(uploadData);

		}

		void CNetworkManager::GetURL()
		{
			FILE* fp = nullptr;
			fopen_s(&fp, m_kNetworkSettingPath.c_str(), "rb");

			if (fp == nullptr)
			{
				//�t�@�C����������Ȃ��B
				nsGameWindow::MessageBoxWarning(L"�l�b�g���[�N�̐ݒ�t�@�C����������܂���B");
				m_networkMode = "NETWORK_OFFLINE";
				return;
			}

			//URL�̒����擾
			int URLLen = 0;
			fread(&URLLen, sizeof(int), 1, fp);

			std::string url = "";

			for (int i = 0;i < URLLen;i++)
			{
				//URL�𕜍�
				//�����L�[�����ڏ����Ă邯��URL���x�^������GitHub�ɂ������肩�͊������}�V�B
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

			//�I�[�v���Ɏ��s�����疳��Ԃ�
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

			//�I�[�v���Ɏ��s�����疳��Ԃ�
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
					// �N���C�A���g�̐ݒ�
					http_client client(m_serverURL);

					// ���M�f�[�^�̍쐬
					json::value postData;

					std::wstring wSaveData = nsUtils::GetWideStringFromString(saveData.c_str());
					postData[L"saveDataCSV"] = json::value::string(wSaveData.c_str());

					// ���N�G�X�g���M
					return client.request(methods::PATCH, L"playerData/" + m_hashCode, postData.serialize(), L"application/json");
				})
			.then([](http_response  response)
				{
					// �X�e�[�^�X�R�[�h����
					if (response.status_code() != status_codes::OK)
					{
						//�A�b�v���[�h�G���[�B�����Q�[�����ɂ͓��ɉe�����Ȃ��B
						nsGameWindow::MessageBoxError(L"�Z�[�u�f�[�^�̃A�b�v���[�h�Ɏ��s���܂����B");
					}
				});
		}
	}
}