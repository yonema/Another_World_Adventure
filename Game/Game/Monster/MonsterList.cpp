#include "MonsterList.h"

namespace nsAWA {

	//ギヤラ
	namespace nsMonster {

		int GetGiyaraAnimationIndex(EnMonsterState state) {

			//アニメーションのindexを定義。
			EnGiyaraAnimation animIndex = EnGiyaraAnimation::enNone;

			//ステートから対応するアニメーションのindexを取得。
			switch (state) {

				//待機
			case EnMonsterState::enIdle:

				//待機アニメーションを設定。
				animIndex = EnGiyaraAnimation::enIdle;
				break;

				//それ以外
			default:
				//設定なしに設定。
				animIndex = EnGiyaraAnimation::enNone;
				break;
			}

			//int型に変換してindexをリターン。
			return static_cast<int>(animIndex);
		}
	}

	//共通のゲッター
	namespace nsMonster {

		int GetAnimationNum(EnMonsterList monster) {

			//モンスターの種類から適切なアニメーション数をリターン。
			switch (monster) {

			case EnMonsterList::enGiyara:
				return static_cast<int>(EnGiyaraAnimation::enNum);
			default:

				nsGameWindow::MessageBoxError(L"モンスターの指定が正しくありません。");
				return -1;
			}
		}

		const char* GetAnimationFilePath(EnMonsterList monster, int animIndex) {

			//モンスターの種類から適切なファイルパスをリターン。
			switch (monster) {

				//ギヤラ
			case EnMonsterList::enGiyara:

				//ギヤラのアニメーションのファイルパスをリターン。
				return kGiyaraAnimFilePaths[animIndex];

			default:

				nsGameWindow::MessageBoxError(L"モンスターの指定が正しくありません。");
				return nullptr;
			}
		}

		int GetAnimationIndex(EnMonsterList monster, EnMonsterState state) {

			//モンスターの種類とステートからから適切なアニメーションをリターン。
			switch (monster) {

				//ギヤラ
			case EnMonsterList::enGiyara:

				//ギヤラの対応アニメーションをリターン。
				return GetGiyaraAnimationIndex(state);

				//それ以外
			default:

				nsGameWindow::MessageBoxError(L"モンスターの指定が正しくありません。");
				return -1;
			}
		}
	}
}