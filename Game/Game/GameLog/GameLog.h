#pragma once

namespace nsAWA {

	namespace nsGameLog {

		class CLogParts;

		//ゲームログクラス
		class CGameLog : nsUtils::SNoncopyable
		{
		public:
			static CGameLog* GetInstance() {

				//インスタンスを生成。
				static CGameLog* instance = new CGameLog;

				//インスタンスをリターン。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void AddGameLog(const std::string& text);

			void Update(float deltaTime);

		private:
			std::list<CLogParts*> m_logParts;		//ログ部品リスト
		};
	}
}