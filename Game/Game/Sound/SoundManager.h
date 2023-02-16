#pragma once

namespace nsAWA {

	namespace nsSound {

		//サウンド管理クラス
		class CSoundManager : nsUtils::SNoncopyable
		{
		public:
			static CSoundManager* GetInstance() {

				//インスタンスを生成。
				static CSoundManager* instance = new CSoundManager;

				//インスタンスをリターン。
				return instance;
			}

			void DeleteInstance() {

				if (m_bgm != nullptr) {

					m_bgm->Stop();
					DeleteGO(m_bgm);

					m_bgm = nullptr;
				}

				//インスタンスを破棄。
				delete GetInstance();
			}

			void AddSound(const std::string& name, CSoundPlayer* sound) {

				//サウンドを追加。
				m_playSoundList.emplace(name, sound);
			}

			void ChangeBGM(const std::string& bgmName);

			void CreateSound(const std::string& soundName);

			CSoundPlayer* SoundRelease(const std::string soundName);

		private:
			std::unordered_map<std::string, CSoundPlayer*> m_playSoundList;	//サウンドリスト
			CSoundPlayer* m_bgm = nullptr;	//BGM
		};
	}
}