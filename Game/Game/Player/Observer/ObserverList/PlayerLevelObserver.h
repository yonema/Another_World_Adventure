#pragma once
#include "../PlayerObserver.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			class CPlayerLevelObserver : public CPlayerObserver
			{
				//経験値テーブルの詳細データ
				enum class EnExpTableVectorInfo {

					enLevel,		//レベル
					enNeedExp		//必要経験値
				};

				void InitSub(CObservablePlayer* observablePlayer)override final;

				void Update(CObservablePlayer* observablePlayer, const std::string& message = "")override final;

			private:
				std::vector<std::vector<int>> m_expTable;		//経験値テーブル
				int m_oldPlayerLevel = 0;					//通知前のプレイヤーのレベル
			};
		}
	}
}

