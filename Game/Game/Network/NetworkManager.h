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
				m_hashCode = hashCode;
			}

			/**
			 * @brief �Z�[�u�f�[�^���T�[�o�[�ɃA�b�v���[�h����
			*/
			void UploadSaveData();

			/**
			 * @brief �A�Z�b�g����Í�������Ă���T�[�o�[URL�𕜍����Ď擾����
			*/
			void GetURL();

			/**
			 * @brief �C���^�[�l�b�g�ɐڑ�����Ă���?
			 * @return �C���^�[�l�b�g�ɐڑ�����Ă��邩
			*/
			bool IsNetworkAccessible();
		private:
			const std::string m_kNetworkSettingPath = "Assets/NetworkSetting/network.cfg";
			const std::string m_kURLKey = "AnotherWorldAdventureAnotherWorldAdventureAnothe";
		private:
			static CNetworkManager* m_instance;					//�C���X�^���X

			std::string m_serverURL = "";						//�ڑ���URL

			std::string m_networkMode = "NETWORK_OFFLINE";		//�C���^�[�l�b�g�ɐڑ�����Ă���?

			std::string m_hashCode = "";						//http�ʐM�Ɏg�p����n�b�V���R�[�h
		};
	}
}
