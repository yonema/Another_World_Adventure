#pragma once
#include "PlayerAnimationEvent.h"

namespace nsAWA {

	namespace nsPlayer {

		//前方宣言
		enum class EnPlayerState;
		namespace nsPlayerAnimation {

			class CPlayerAnimationBase;
		}
		
		namespace nsPlayerAnimation {

			//プレイヤーアニメーション
			class CPlayerAnimation : nsUtils::SNoncopyable
			{
				//アニメーションのタイプ
				enum class EnAnimType {

					enSword,	//剣
					enAxe,		//斧
					enWand,		//杖

					enNum,		//タイプの数
					enNone		//設定なし
				};

			public:
				//アニメーションの名前（全て）
				enum class EnAnimName {

					enSword_Idle,	//剣待機
					enSword_Walk,	//剣歩く
					enSword_Dash,	//剣走る
					enSword_WeakAttack_A,	//剣弱攻撃A
					enSword_StrongAttack,	//剣強攻撃
					enSword_Damage,	//剣被弾
					enSword_Death,	//剣死亡
					enSword_Guard,	//剣ガード
					enSword_UseItem,	//剣アイテム使用
					enSword_Stun,	//剣スタン

					enNum,			//アニメーション数
					enNone			//名前なし
				};
			private:

				//アニメーション情報
				enum class EnAnimInfo {

					enFilePath,			//ファイルパス
					enSpeed,			//速度
					enLoopFlag,			//ループフラグ
					enAnimationEvent	//アニメーションイベント
				};

				//アニメーションデータ
				struct SAnimData {

					EnAnimName animName = EnAnimName::enNone;	//アニメーションの番号
					float speed = 0.0f;							//速度
					bool enLoopFlag = false;					//ループフラグ
					std::list<std::string> animationEvent;		//アニメーションイベント
				};
			public:
				void Init(CPlayerInput* playerInput);

				std::string* GetAnimFilePath()const {

					//アニメーションのファイルパスをリターン。
					return m_animFilePaths;
				}

				void Update(bool changeState, EnPlayerState playerState);

				void SetPlayerModelAndAnimEvent(CModelRenderer* playerModel);

				void Release();

			private:
				void PlayAnimation(EnPlayerState playerState);

				void LoadAnimation();

			private:
				static std::string m_animFilePaths[static_cast<int>(EnAnimName::enNum)];		//アニメーションのファイルパス

				CModelRenderer* m_playerModel = nullptr;	//プレイヤーモデル
				EnAnimType m_type = EnAnimType::enNone;		//アニメーションのタイプ
				CPlayerAnimationBase* m_playerAnimation[static_cast<int>(EnAnimType::enNum)] = { nullptr };		//各アニメーション
				CPlayerAnimationEvent m_animationEvent;		//プレイヤーのアニメーションイベント

				std::vector<SAnimData> m_animDataList;	//アニメーションデータ
			};
		}
	}
}