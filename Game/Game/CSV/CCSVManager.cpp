#include <fstream>
#include <sstream>
#include "YonemaEnginePreCompile.h"
#include "CCSVManager.h"

namespace nsAWA {

	namespace nsCSV {

		void CCsvManager::LoadCSV(const char* csvFilePath) {

			//csv�t�@�C�����J���B
			std::ifstream ifStream(csvFilePath);

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