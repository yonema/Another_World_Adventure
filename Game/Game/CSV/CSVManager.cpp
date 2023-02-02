#include <fstream>
#include <sstream>
#include "YonemaEnginePreCompile.h"
#include "CSVManager.h"

namespace nsAWA {

	namespace nsCSV {

		void CCsvManager::LoadCSV(const wchar_t* csvFilePath) {

			//csv�t�@�C�����J���B
			std::ifstream ifStream(csvFilePath);

			//csv�t�@�C���̓ǂݍ��݂Ɏ��s�����B
			if (!ifStream) {
				
				//�G���[�o�́B
				nsGameWindow::MessageBoxError(L"CSV�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B");
			}

			//csv����̕�����i�[�p�̕ϐ����`�B
			std::string lineStr;

			//CSV�t�@�C���̍Ō�̍s�܂�1�s�����ׂ�B
			while (getline(ifStream, lineStr)) {

				//���񂾕�������J���}��؂�ŕ������A�i�[�B
				std::vector<std::string> strVec = Split(lineStr, ',');

				//���X�g�Ɋi�[�B
				m_csvData.emplace_back(strVec);
			}
		}

		void CCsvManager::SaveCSV(const wchar_t* csvFilePath, const std::list<std::vector<std::string>>& m_csvData) {

			//wchar_t����char�ɕϊ��B
			char objName[256];
			size_t ret;
			wcstombs_s(&ret, objName, 256, csvFilePath, _TRUNCATE);

			//�O��̃f�[�^�t�@�C�����폜����B
			remove(objName);

			//��������CSV�t�@�C�����J���B
			std::ofstream ofs(objName);

			//�������ރf�[�^�����ɎQ�ƁB
			for (const auto& dataList : m_csvData) {

				for (const auto& data : dataList) {

					//�������ށB
					ofs << data << ',';
				}

				//���s�B
				ofs << std::endl;
			}
		}

		std::vector<std::string> CCsvManager::Split(std::string& input, char delimiter) {

			//getline()�֐����g�����߁A�������istringstream�^�ɕϊ��B
			std::istringstream stream(input);

			//������i�[�p�̕ϐ����`�B
			std::string field;

			//�ŏI�I�ȕ�����̔z����`�B
			std::vector<std::string> result;

			//�s�̍Ō�܂�delimiter�ŋ�؂�ꂽ�������field�Ɋi�[�B
			while (getline(stream, field, delimiter)) {

				//��񂪂Ȃ�������X�L�b�v�B
				if (field == "") { continue; }

				//�z��ɒǉ��B
				result.emplace_back(field);
			}

			//��؂�ꂽ1�s���̕�����̔z������^�[���B
			return result;
		}
	}
}