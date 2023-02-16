#pragma once

namespace nsAWA {

	namespace nsSound {

		//サウンドリスト
		class CSoundList : nsUtils::SNoncopyable
		{
		public:
			//サウンドデータ
			struct SSoundData {

				std::string name = "NoName";	//名前
				std::string type = "NoType";	//種類（BGM,SE）
				bool isLoop = false;			//ループフラグ
				float volume = 1.0f;			//音量
			};

		public:
			static CSoundList* GetInstance() {

				//インスタンスを生成。
				static CSoundList* instance = new CSoundList;
				
				//インスタンスを取得。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadSoundList();

			const SSoundData& GetSoundData(const std::string& soundName)const;

		private:
			std::list<SSoundData> m_soundList;	//サウンドリスト
		};

		//サウンド生成クラス。
		class CSoundBuilder : nsUtils::SNoncopyable {

		public:
			CSoundPlayer* Create(const std::string& soundName);

		};
	}
}