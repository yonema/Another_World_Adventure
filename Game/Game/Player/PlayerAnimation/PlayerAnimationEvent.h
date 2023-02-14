#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;
	namespace nsPlayer {

		class CPlayerInput;
		class CPlayerAction;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//エイリアス宣言
			using AnimationEventDataStr = std::list<std::vector<std::string>>;

			//アニメーションイベントデータ
			struct SAnimationEventData {
				
				std::string eventName = "NoName";					//イベント名
				std::string detailStr = "None";						//イベント詳細データ
			};
			//プレイヤーアニメーションイベントクラス
			class CPlayerAnimationEvent : nsUtils::SNoncopyable
			{
			public:
				void Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction, CPlayerAnimation* playerAnimation) {

					//各ポインタを格納。
					m_player = player;
					m_playerInput = playerInput;
					m_playerAction = playerAction;
					m_playerAnimation = playerAnimation;
				}

				void Update();

				void CoolTimeOn();

				void CoolTimeOff();

				void InputEnable();

				void CreateTrigger(const std::string& triggerIndexStr);

				void MoveStart();

				void MoveEnd();

				void Move();

				void CreateMagic();

				void GetAnimationEvent(const std::string& animationEventName, const std::string& detailStr);

			private:
				IGameActor* m_player = nullptr;			//プレイヤーのポインタ
				CPlayerInput* m_playerInput = nullptr;	//プレイヤー入力クラス
				CPlayerAction* m_playerAction = nullptr;//プレイヤーアクションクラス
				CPlayerAnimation* m_playerAnimation = nullptr;//プレイヤーアニメーションクラス
				bool m_isMoving = false;				//イベントによって移動している？
				CVector3 m_playerMoveInput = CVector3::Zero();	//プレイヤーの入力方向

				std::unordered_map<std::string, AnimationEventDataStr> m_animEventDataList;	//アニメーションイベントデータ
			};
		}
	}
}