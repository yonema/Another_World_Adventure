#include <fstream>
#include <sstream>
#include "YonemaEnginePreCompile.h"
#include "CCSVManager.h"

namespace nsAWA {

	namespace nsCSV {

		void CCsvManager::LoadCSV(const char* csvFilePath) {

			//csvファイルを開く。
			std::ifstream ifStream(csvFilePath);

			//csvからの文字列格納用の変数を定義。
			std::string lineStr;

			//CSVファイルの最後の行まで1行ずつ調べる。
			while (getline(ifStream, lineStr)) {

				//並んだ文字列をカンマ区切りで分割し、格納。
				std::vector<std::string> strVec = Split(lineStr, ',');

				//リストに格納。
				m_csvData.emplace_back(strVec);
			}
		}

		std::vector<std::string> CCsvManager::Split(std::string& input, char delimiter) {

			//getline()関数を使うため、文字列をistringstream型に変換。
			std::istringstream stream(input);

			//文字列格納用の変数を定義。
			std::string field;

			//最終的な文字列の配列を定義。
			std::vector<std::string> result;

			//行の最後までdelimiterで区切られた文字列をfieldに格納。
			while (getline(stream, field, delimiter)) {

				//情報がなかったらスキップ。
				if (field == "") { continue; }

				//配列に追加。
				result.emplace_back(field);
			}

			//区切られた1行分の文字列の配列をリターン。
			return result;
		}
	}
}