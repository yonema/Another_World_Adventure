#include "YonemaEnginePreCompile.h"
#include "MagicList.h"
#include "../CSV/CSVManager.h"
#include "MagicBallOne.h"
#include "MagicBallSide.h"
#include "MagicBallForward.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr const wchar_t* kMagicListCSVFilePath = L"Assets/CSV/MagicList.csv";	//魔法のリストのCSVのファイルパス	
		}

		void CMagicList::LoadMagicList() {

			//CSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kMagicListCSVFilePath);

			//魔法データの雛形を生成。
			SMagicData magicDataBase;

			//魔法データを取得。
			auto magicDataStr = csvManager.GetCsvData();

			//魔法データを順に参照。
			for (auto& lineData : magicDataStr) {

				//見出しを取得。
				std::string title = lineData[0];

				if (title == "*") {

					//情報の終端なので情報を追加。

					//データを格納。
					m_magicList.emplace_back(magicDataBase);

					//魔法データの雛形を初期化。
					SMagicData clearData;
					magicDataBase = clearData;

					//次へ。
					continue;
				}

				//魔法データを取得。
				if (title == "NAME") {

					magicDataBase.name = lineData[1];
				}
				else if(title == "TYPE") {

					magicDataBase.magicType = lineData[1];
				}
				else if (title == "FEATURE") {

					lineData.erase(lineData.begin());
					magicDataBase.featureList.emplace_back(lineData);
				}
			}
		}

		const CMagicList::SMagicData& CMagicList::GetMagicData(const std::string& name)const {

			//魔法リストを順に参照。
			for (const auto& magic : m_magicList) {

				//同じ名前の魔法が見つかったら。
				if (magic.name == name) {

					//その魔法の情報をリターン。
					return magic;
				}
			}

			//エラー出力。
			std::string errorMsg = "CMagicList : 魔法が見つかりませんでした。 : ";
			errorMsg += name;
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

			std::abort();
		}

		CMagicBase* CMagicBuilder::CreateMagic(const std::string& magicName) {

			//魔法リストのインスタンスを取得。
			auto magicList = CMagicList::GetInstance();

			//名前から魔法の情報を取得。
			CMagicList::SMagicData magicData = magicList->GetMagicData(magicName);

			//魔法タイプを取得。
			std::string magicType = magicData.magicType;

			CMagicBase* magic = nullptr;

			//魔法を生成。
			if (magicType == "One") {

				magic = NewGO<CMagicBallOne>();
			}
			else if (magicType == "Side") {

				magic = NewGO<CMagicBallSide>();
			}
			else if (magicType == "Forward") {

				magic = NewGO<CMagicBallForward>();
			}

			//名前を設定。
			magic->SetMagicName(magicData.name);

			//効果のリストを設定。
			magic->SetFeatureList(magicData.featureList);

			return magic;
		}
	}
}