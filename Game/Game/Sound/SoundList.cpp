#include "YonemaEnginePreCompile.h"
#include "SoundList.h"
#include "../CSV/CSVManager.h"
#include "SoundManager.h"

namespace nsAWA {

	namespace nsSound {

		namespace {

			constexpr const wchar_t* kSoundCSVFilePath = L"Assets/CSV/SoundList.csv";	//�T�E���h��CSV�̃��X�g
		}

		void CSoundList::LoadSoundList() {

			//CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kSoundCSVFilePath);

			//�T�E���h�f�[�^�̐��`�𐶐��B
			SSoundData soundDataBase;

			for (const auto& soundData : csvManager.GetCsvData()) {

				//���o�����擾�B
				std::string title = soundData[0];

				if (title == "*") {

					//�f�[�^�����X�g�ɒǉ��B
					m_soundList.emplace_back(soundDataBase);

					//�������B
					SSoundData soundDataInit;
					soundDataBase = soundDataInit;

					//���ցB
					continue;
				}

				if (title == "NAME") {

					//���O���擾�B
					soundDataBase.name = soundData[1];
					
					//���ցB
					continue;
				}
				else if (title == "TYPE") {
					
					//��ނ��擾�B
					soundDataBase.type = soundData[1];

					//���ցB
					continue;
				}
				else if (title == "LOOP") {

					//���[�v�t���O���擾�B
					soundDataBase.isLoop = soundData[1] == "TRUE" ? true : false;
				}
				else if (title == "VOLUME") {

					//���ʂ��擾�B
					soundDataBase.volume = std::stof(soundData[1]);

					//���ցB
					continue;
				}
			}
		}

		const CSoundList::SSoundData& CSoundList::GetSoundData(const std::string& soundName)const {

			//���X�g�����ɎQ�ƁB
			for (const auto& soundData : m_soundList) {

				//�������O�̃T�E���h������������B
				if (soundData.name == soundName) {

					//���̃T�E���h�f�[�^�����^�[���B
					return soundData;
				}
			}
			std::string errorMsg = "CSoundList : �T�E���h�f�[�^��������܂���ł����B : ";
			errorMsg += soundName;
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
		}

		CSoundPlayer* CSoundBuilder::Create(const std::string& soundName) {

			//���O����T�E���h���擾�B
			CSoundList::SSoundData soundData = CSoundList::GetInstance()->GetSoundData(soundName);
			EnSubmixType type = EnSubmixType::enNum;

			if (soundData.type == "BGM") {

				type = EnSubmixType::enBGM;
			}
			else if (soundData.type == "SE") {

				type = EnSubmixType::enSE;
			}

			//�t�@�C���p�X��ݒ�B
			std::string soundFilePath = "Assets/Sounds/";
			soundFilePath += soundData.type;
			soundFilePath += "/";
			soundFilePath += soundData.name;
			soundFilePath += ".wav";

			//�T�E���h�𐶐��B
			CSoundPlayer* sound = NewGO<CSoundPlayer>();
			sound->Init(soundFilePath.c_str(), type, soundData.isLoop);

			//���ʂ�ݒ�B
			sound->SetVolume(soundData.volume);

			return sound;
		}
	}
}