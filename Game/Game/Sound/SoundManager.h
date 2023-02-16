#pragma once

namespace nsAWA {

	namespace nsSound {

		//�T�E���h�Ǘ��N���X
		class CSoundManager : nsUtils::SNoncopyable
		{
		public:
			static CSoundManager* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CSoundManager* instance = new CSoundManager;

				//�C���X�^���X�����^�[���B
				return instance;
			}

			void DeleteInstance() {

				if (m_bgm != nullptr) {

					m_bgm->Stop();
					DeleteGO(m_bgm);

					m_bgm = nullptr;
				}

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void AddSound(const std::string& name, CSoundPlayer* sound) {

				//�T�E���h��ǉ��B
				m_playSoundList.emplace(name, sound);
			}

			void ChangeBGM(const std::string& bgmName);

			void CreateSound(const std::string& soundName);

			CSoundPlayer* SoundRelease(const std::string soundName);

		private:
			std::unordered_map<std::string, CSoundPlayer*> m_playSoundList;	//�T�E���h���X�g
			CSoundPlayer* m_bgm = nullptr;	//BGM
		};
	}
}