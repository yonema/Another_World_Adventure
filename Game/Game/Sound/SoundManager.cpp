#include "YonemaEnginePreCompile.h"
#include "SoundManager.h"
#include "SoundList.h"

namespace nsAWA {

	namespace nsSound {

		CSoundPlayer* CSoundManager::SoundRelease(const std::string soundName) {

			//�T�E���h��j���B
			auto* soundRef = m_playSoundList.at(soundName);
			soundRef->Stop();
			DeleteGO(soundRef);
			m_playSoundList.erase(m_playSoundList.find(soundName));
		}

		void CSoundManager::ChangeBGM(const std::string& bgmName) {

			//���ɓ����Ă���Ȃ�B
			if (m_bgm != nullptr) {

				//�j���B
				m_bgm->Stop();
				DeleteGO(m_bgm);

				m_bgm = nullptr;
			}

			CSoundBuilder soundBuilder;
			m_bgm = soundBuilder.Create(bgmName);
			m_bgm->Play();
		}

		void CSoundManager::CreateSound(const std::string& soundName) {

			//�T�E���h�𐶐��B
			CSoundBuilder soundBuilder;
			CSoundPlayer* sound = soundBuilder.Create(soundName);
			sound->Play();
		}
	}
}