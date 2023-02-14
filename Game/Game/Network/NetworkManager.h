#pragma once

namespace nsAWA
{
	namespace nsNetwork
	{
		class CNetworkManager
		{
		private:
			CNetworkManager() {}
			~CNetworkManager() {}

		public:
			/**
			 * @brief �C���X�^���X���쐬
			 * @return �C���X�^���X
			*/
			static inline CNetworkManager* CreateInstance(std::string networkMode) noexcept
			{
				if (m_instance == nullptr)
				{
					m_instance = new CNetworkManager();

					//�l�b�g���[�N���[�h��ݒ�
					m_instance->m_networkMode = networkMode;

					//�ڑ���URL��ǂݍ���
					m_instance->GetURL();
				}
				return m_instance;
			}

			/**
			 * @brief �C���X�^���X���擾
			 * @return �C���X�^���X
			*/
			static inline CNetworkManager* GetInstance() noexcept
			{
				return m_instance;
			}

			/**
			 * @brief �C���X�^���X���폜
			 * @return
			*/
			static void DeleteInstance() noexcept
			{
				if (m_instance == nullptr)
				{
					return;
				}
				delete m_instance;
				m_instance = nullptr;
			}

			/**
			 * @brief �n�b�V���R�[�h��o�^
			 * @param hashCode �n�b�V���R�[�h
			*/
			void SetHashCode(std::string hashCode)
			{
				m_hashCode = nsUtils::GetWideStringFromString(hashCode.c_str());
			}

			/**
			 * @brief �Z�[�u�f�[�^���T�[�o�[�ɃA�b�v���[�h����
			*/
			void UploadSaveData();
		private:
			/**
			 * @brief �A�Z�b�g����Í�������Ă���T�[�o�[URL�𕜍����Ď擾����
			*/
			void GetURL();

			/**
			 * @brief �C���^�[�l�b�g�ɐڑ�����Ă���?
			 * @return �C���^�[�l�b�g�ɐڑ�����Ă��邩
			*/
			bool IsNetworkAccessible();

			/**
			 * @brief ���[�J���ɂ���Z�[�u�f�[�^���擾����
			 * @return �Z�[�u�f�[�^
			*/
			std::string LoadLocalSaveData();

			/**
			 * @brief �Z�[�u�f�[�^��http�ʐM�ŃA�b�v���[�h���X�V����
			 * @param saveData �Z�[�u�f�[�^
			*/
			void HttpUpload(const std::string& saveData);
		private:
			const std::string m_kNetworkSettingPath = "Assets/NetworkSetting/network.cfg";		//�l�b�g���[�N�̐ݒ�t�@�C��
			const std::string m_kURLKey = "AnotherWorldAdventureAnotherWorldAdventureAnothe";	//�l�b�g���[�N���M��̕����L�[
			const std::string m_kSaveDataPath = "Assets/CSV/UserData.csv";						//���[�J���̃Z�[�u�f�[�^�̕ۑ��ꏊ
		private:
			static CNetworkManager* m_instance;					//�C���X�^���X

			std::wstring m_serverURL = L"";						//�ڑ���URL

			std::string m_networkMode = "NETWORK_OFFLINE";		//�C���^�[�l�b�g�ɐڑ�����Ă���?

			std::wstring m_hashCode = L"";						//http�ʐM�Ɏg�p����n�b�V���R�[�h
		};
	}
}
