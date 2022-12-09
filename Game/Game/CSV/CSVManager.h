#pragma once

namespace nsAWA {

	namespace nsCSV {

		//CSV�Ǘ��N���X
		class CCsvManager : nsUtils::SNoncopyable{

		public:
			void LoadCSV(const wchar_t* csvFilePath);
			std::vector<std::string> Split(std::string& input, char delimiter);

			std::list<std::vector<std::string>> GetCsvData() {

				return m_csvData;
			}
		private:
			std::list<std::vector<std::string>> m_csvData;
		};
	}
}