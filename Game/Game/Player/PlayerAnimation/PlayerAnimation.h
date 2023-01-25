#pragma once
#include "PlayerAnimationEvent.h"

namespace nsAWA {

	//前方宣言
	namespace nsSkill {

		class CActiveSkill;
	}
	namespace nsPlayer {
		
		enum class EnPlayerState;
	}

	namespace nsPlayer {
		
		namespace nsPlayerAnimation {

			//アニメーションのタイプ
			enum class EnAnimType {

				enSword,	//剣
				enAxe,		//斧
				enWand,		//杖

				enNum,		//タイプの数
				enNone		//設定なし

			};

			//アニメーションデータ
			struct SAnimData {

				std::string animName = "NoName";	//アニメーション名
				int animNum = -1;					//アニメーションの番号
				float speed = 0.0f;							//速度
				bool isLoopAnim = false;					//ループフラグ
				std::vector<SAnimationEventData> animationEvent;			//アニメーションイベント
			};

			//プレイヤーアニメーションクラス
			class CPlayerAnimation : nsUtils::SNoncopyable
			{
			public:
				void Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction);

				void Release();

				const std::vector<std::string>& GetAnimFilePath()const {

					//アニメーションのファイルパスをリターン。
					return m_animFilePathArray;
				}

				void Update(bool changeState, EnPlayerState playerState);

				void SetPlayerModelAndAnimEvent(CModelRenderer* playerModel);

				void ReserveActiveSkillAnimation(nsSkill::CActiveSkill* activeSkill) {

					//アクティブスキルのアニメーション再生を予約するため、情報を取得。
					m_activeSkill = activeSkill;
				}

			private:
				void PlayAnimation(EnPlayerState playerState);

				const SAnimData& GetAnimationData(EnPlayerState playerState);

				void LoadAnimation();

				const std::string& GetActiveSkillName()const;

			private:
				CModelRenderer* m_playerModel = nullptr;	//プレイヤーモデル
				EnAnimType m_type = EnAnimType::enNone;		//アニメーションのタイプ
				CPlayerAnimationEvent m_animationEvent;		//プレイヤーのアニメーションイベント
				nsSkill::CActiveSkill* m_activeSkill = nullptr;	//アクティブスキルのポインタ

				std::vector<SAnimData> m_animDataList;	//アニメーションデータ
				std::vector<std::string> m_animFilePathArray;	//アニメーションのファイルパスの配列
			};
		}
	}
}