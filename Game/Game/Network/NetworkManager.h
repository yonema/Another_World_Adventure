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

					//ネットワークモードを設定
					m_instance->m_networkMode = networkMode;

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
				m_hashCode = nsUtils::GetWideStringFromString(hashCode.c_str());
			}

			/**
			 * @brief セーブデータをサーバーにアップロードする
			*/
			void UploadSaveData();
		private:
			/**
			 * @brief アセットから暗号化されているサーバーURLを復号して取得する
			*/
			void GetURL();

			/**
			 * @brief インターネットに接続されている?
			 * @return インターネットに接続されているか
			*/
			bool IsNetworkAccessible();

			/**
			 * @brief ローカルにあるセーブデータを取得する
			 * @return セーブデータ
			*/
			std::string LoadLocalSaveData();

			/**
			 * @brief セーブデータをhttp通信でアップロードし更新する
			 * @param saveData セーブデータ
			*/
			void HttpUpload(const std::string& saveData);
		private:
			const std::string m_kNetworkSettingPath = "Assets/NetworkSetting/network.cfg";		//ネットワークの設定ファイル
			const std::string m_kURLKey = "AnotherWorldAdventureAnotherWorldAdventureAnothe";	//ネットワーク送信先の復号キー
			const std::string m_kSaveDataPath = "Assets/CSV/UserData.csv";						//ローカルのセーブデータの保存場所
		private:
			static CNetworkManager* m_instance;					//インスタンス

			std::wstring m_serverURL = L"";						//接続先URL

			std::string m_networkMode = "NETWORK_OFFLINE";		//インターネットに接続されている?

			std::wstring m_hashCode = L"";						//http通信に使用するハッシュコード
		};
	}
}
