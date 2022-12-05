#pragma once

namespace nsAWA {

	namespace nsCSV {

		//CSV�Ǘ��N���X
		class CCsvManager {

		public:
			void LoadCSV(const char* csvFilePath);
			std::vector<std::string> Split(std::string& input, char delimiter);

			std::list<std::vector<std::string>> GetCsvData() {

				return m_csvData;
			}
		private:
			std::list<std::vector<std::string>> m_csvData;
		};
	}
}