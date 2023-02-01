#pragma once

namespace nsAWA {

	namespace nsCSV {

		//CSV�Ǘ��N���X
		class CCsvManager : nsUtils::SNoncopyable{

		public:
			void LoadCSV(const wchar_t* csvFilePath);

			void SaveCSV(const wchar_t* csvFilePath, const std::list<std::vector<std::string>>& m_csvData);

			void ClearCSV() {

				//�f�[�^��j���B
				m_csvData.clear();
			}
			
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