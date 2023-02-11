#include "YonemaEnginePreCompile.h"
#include "GameLog.h"
#include "LogParts.h"

namespace nsAWA {

	namespace nsGameLog {

		void CGameLog::AddGameLog(const std::string& text) {

			//ログ部品の座標をずらす。
			for (const auto& logPart : m_logParts) {

				logPart->AddPosition();
			}

			//wstringに変換。
			std::wstring wText = L"--";
			wText += nsUtils::GetWideStringFromString(text);

			//ログ部品を生成。
			CLogParts* logParts = NewGO<CLogParts>();
			logParts->Create(wText);

			//ログ部品を追加。
			m_logParts.emplace_back(logParts);
		}

		void CGameLog::Update(float deltaTime) {


			for (auto itr = m_logParts.begin(); itr != m_logParts.end();) {

				//表示が終わっていたら。
				if ((*itr)->IsEnd()) {

					//ログ部品を破棄。
					(*itr)->Release();

					//リストから破棄。
					itr = m_logParts.erase(itr);

					//次へ。
					continue;
				}

				//イテレータを進める。
				itr++;
			}
		}
	}
}