#pragma once

namespace nsAWA {

	namespace nsCSV {

		//CSVŠÇ—ƒNƒ‰ƒX
		class CCsvManager : nsUtils::SNoncopyable{

		public:
			void LoadCSV(const wchar_t* csvFilePath);
			
			std::list<std::vector<std::string>> GetCsvData() {

				return m_csvData;
			}

		private:
			std::vector<std::string> Split(std::string& input, char delimiter);

		private:
			std::list<std::vector<std::string>> m_csvData;
		};
	}
}