#include "YonemaEnginePreCompile.h"
#include "SoundList.h"
#include "../CSV/CSVManager.h"
#include "SoundManager.h"

namespace nsAWA {

	namespace nsSound {

		namespace {

			constexpr const wchar_t* kSoundCSVFilePath = L"Assets/CSV/SoundList.csv";	//サウンドのCSVのリスト
		}

		void CSoundList::LoadSoundList() {

			//CSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kSoundCSVFilePath);

			//サウンドデータの雛形を生成。
			SSoundData soundDataBase;

			for (const auto& soundData : csvManager.GetCsvData()) {

				//見出しを取得。
				std::string title = soundData[0];

				if (title == "*") {

					//データをリストに追加。
					m_soundList.emplace_back(soundDataBase);

					//初期化。
					SSoundData soundDataInit;
					soundDataBase = soundDataInit;

					//次へ。
					continue;
				}

				if (title == "NAME") {

					//名前を取得。
					soundDataBase.name = soundData[1];
					
					//次へ。
					continue;
				}
				else if (title == "TYPE") {
					
					//種類を取得。
					soundDataBase.type = soundData[1];

					//次へ。
					continue;
				}
				else if (title == "LOOP") {

					//ループフラグを取得。
					soundDataBase.isLoop = soundData[1] == "TRUE" ? true : false;
				}
				else if (title == "VOLUME") {

					//音量を取得。
					soundDataBase.volume = std::stof(soundData[1]);

					//次へ。
					continue;
				}
			}
		}

		const CSoundList::SSoundData& CSoundList::GetSoundData(const std::string& soundName)const {

			//リストを順に参照。
			for (const auto& soundData : m_soundList) {

				//同じ名前のサウンドが見つかったら。
				if (soundData.name == soundName) {

					//そのサウンドデータをリターン。
					return soundData;
				}
			}
			std::string errorMsg = "CSoundList : サウンドデータが見つかりませんでした。 : ";
			errorMsg += soundName;
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
		}

		CSoundPlayer* CSoundBuilder::Create(const std::string& soundName) {

			//名前からサウンドを取得。
			CSoundList::SSoundData soundData = CSoundList::GetInstance()->GetSoundData(soundName);
			EnSubmixType type = EnSubmixType::enNum;

			if (soundData.type == "BGM") {

				type = EnSubmixType::enBGM;
			}
			else if (soundData.type == "SE") {

				type = EnSubmixType::enSE;
			}

			//ファイルパスを設定。
			std::string soundFilePath = "Assets/Sounds/";
			soundFilePath += soundData.type;
			soundFilePath += "/";
			soundFilePath += soundData.name;
			soundFilePath += ".wav";

			//サウンドを生成。
			CSoundPlayer* sound = NewGO<CSoundPlayer>();
			sound->Init(soundFilePath.c_str(), type, soundData.isLoop);

			//音量を設定。
			sound->SetVolume(soundData.volume);

			return sound;
		}
	}
}