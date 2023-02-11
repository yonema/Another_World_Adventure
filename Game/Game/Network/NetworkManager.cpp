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

			//�A�b�v���[�h����

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

			m_serverURL = url;

			fclose(fp);

		}
	}
}