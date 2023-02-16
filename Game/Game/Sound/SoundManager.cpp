#include "YonemaEnginePreCompile.h"
#include "SoundManager.h"
#include "SoundList.h"

namespace nsAWA {

	namespace nsSound {

		CSoundPlayer* CSoundManager::SoundRelease(const std::string soundName) {

			//サウンドを破棄。
			auto* soundRef = m_playSoundList.at(soundName);
			soundRef->Stop();
			DeleteGO(soundRef);
			m_playSoundList.erase(m_playSoundList.find(soundName));
		}

		void CSoundManager::ChangeBGM(const std::string& bgmName) {

			//既に入っているなら。
			if (m_bgm != nullptr) {

				//破棄。
				m_bgm->Stop();
				DeleteGO(m_bgm);

				m_bgm = nullptr;
			}

			CSoundBuilder soundBuilder;
			m_bgm = soundBuilder.Create(bgmName);
			m_bgm->Play();
		}

		void CSoundManager::CreateSound(const std::string& soundName) {

			//サウンドを生成。
			CSoundBuilder soundBuilder;
			CSoundPlayer* sound = soundBuilder.Create(soundName);
			sound->Play();
		}
	}
}