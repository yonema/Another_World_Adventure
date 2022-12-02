#pragma once

namespace nsAWA {

	/**
	 * @brief モンスターのステートとリスト
	*/
	namespace nsMonster {

		//モンスターのステート
		enum class EnMonsterState {

			enIdle,		//待機

			enNum,		//ステートの数
			enNone = -1	//設定なし
		};

		//モンスターのリスト
		enum class EnMonsterList {

			enGiyara,		//ギヤラ

			enNum,			//モンスターの種類の数
			enNone = -1		//設定なし
		};

	}

	/**
	 * @brief ギヤラ
	*/
	namespace nsMonster {

		//ギヤラのアニメーション
		enum class EnGiyaraAnimation {

			enIdle,			//待機

			enNum,			//アニメーションの数
			enNone = -1		//設定なし
		};

		//ギヤラのアニメーションのファイルパス
		constexpr const char* kGiyaraAnimFilePaths[static_cast<int>(EnGiyaraAnimation::enNum)] = {

			"Assets/Animations/Monster/Giyara/Giyara_Idle.fbx",
		};

		int GetGiyaraAnimationIndex(EnMonsterState state);
	}

	/**
	 * @brief 共通のゲッター
	*/
	namespace nsMonster {

		int GetAnimationNum(EnMonsterList monster);

		const char* GetAnimationFilePath(EnMonsterList monster, int animIndex);

		int GetAnimationIndex(EnMonsterList monster, EnMonsterState state);
	}
}