#include "YonemaEnginePreCompile.h"
#include "GameLog.h"
#include "LogParts.h"

namespace nsAWA {

	namespace nsGameLog {

		void CGameLog::AddGameLog(const std::string& text) {

			//���O���i�̍��W�����炷�B
			for (const auto& logPart : m_logParts) {

				logPart->AddPosition();
			}

			//wstring�ɕϊ��B
			std::wstring wText = L"--";
			wText += nsUtils::GetWideStringFromString(text);

			//���O���i�𐶐��B
			CLogParts* logParts = NewGO<CLogParts>();
			logParts->Create(wText);

			//���O���i��ǉ��B
			m_logParts.emplace_back(logParts);
		}

		void CGameLog::Update(float deltaTime) {


			for (auto itr = m_logParts.begin(); itr != m_logParts.end();) {

				//�\�����I����Ă�����B
				if ((*itr)->IsEnd()) {

					//���O���i��j���B
					(*itr)->Release();

					//���X�g����j���B
					itr = m_logParts.erase(itr);

					//���ցB
					continue;
				}

				//�C�e���[�^��i�߂�B
				itr++;
			}
		}
	}
}