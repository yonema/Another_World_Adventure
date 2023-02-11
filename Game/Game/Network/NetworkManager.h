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
			 * @brief インスタンスを作成
			 * @return インスタンス
			*/
			static inline CNetworkManager* CreateInstance(std::string networkMode) noexcept
			{
				if (m_instance == nullptr)
				{
					m_instance = new CNetworkManager();

					//接続先URLを読み込み
					m_instance->GetURL();
				}
				return m_instance;
			}

			/**
			 * @brief インスタンスを取得
			 * @return インスタンス
			*/
			static inline CNetworkManager* GetInstance() noexcept
			{
				return m_instance;
			}

			/**
			 * @brief インスタンスを削除
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
			 * @brief ハッシュコードを登録
			 * @param hashCode ハッシュコード
			*/
			void SetHashCode(std::string hashCode)
			{
				m_hashCode = hashCode;
			}

			/**
			 * @brief セーブデータをサーバーにアップロードする
			*/
			void UploadSaveData();

			/**
			 * @brief アセットから暗号化されているサーバーURLを復号して取得する
			*/
			void GetURL();

			/**
			 * @brief インターネットに接続されている?
			 * @return インターネットに接続されているか
			*/
			bool IsNetworkAccessible();
		private:
			const std::string m_kNetworkSettingPath = "Assets/NetworkSetting/network.cfg";
			const std::string m_kURLKey = "AnotherWorldAdventureAnotherWorldAdventureAnothe";
		private:
			static CNetworkManager* m_instance;					//インスタンス

			std::string m_serverURL = "";						//接続先URL

			std::string m_networkMode = "NETWORK_OFFLINE";		//インターネットに接続されている?

			std::string m_hashCode = "";						//http通信に使用するハッシュコード
		};
	}
}
