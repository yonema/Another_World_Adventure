#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//エイリアス宣言
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
					//enAxe_Idle,	//剣待機
					//enWand_Idle,	//剣待機

					enNum			//アニメーション数
				};

				void Init();

				SAnimationInitData* GetAnimData() {

					//アニメーションのデータをリターン。
					return m_sAnimationInitData;
				}

				void UpdateAnimation(EnPlayerState playerState);

				void SetPlayerModel(CModelRenderer* playerModel) {

					//プレイヤーモデルを設定。
					m_playerModel = playerModel;
				}

				void Release();
			private:
				static const char* m_kAnimFilePaths[static_cast<int>(EnAnimName::enNum)];		//アニメーションのファイルパス

				SAnimationInitData* m_sAnimationInitData = nullptr;	//アニメーションデータ
				CModelRenderer* m_playerModel = nullptr;	//プレイヤーモデル
				EnAnimType m_type = EnAnimType::enNone;		//アニメーションのタイプ
				CPlayerAnimationBase* m_playerAnimation[static_cast<int>(EnAnimType::enNum)] = { nullptr };		//各アニメーション
			};
		}
	}
}