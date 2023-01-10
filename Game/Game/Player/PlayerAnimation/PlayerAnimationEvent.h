#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;
	namespace nsPlayer {

		class CPlayerInput;
		class CPlayerAction;
	}

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//エイリアス宣言
			using AnimationEventDataStr = std::list<std::vector<std::string>>;

			//アニメーションイベントデータ
			struct SAnimationEventData {
				
				std::string eventName = "NoName";					//イベント名
				bool hasEventMaterial = false;						//イベントに必要な材料がある？
				AnimationEventDataStr eventData;					//イベント材料
			};
			//プレイヤーアニメーションイベントクラス
			class CPlayerAnimationEvent : nsUtils::SNoncopyable
			{
			public:
				void Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction) {

					//各ポインタを格納。
					m_player = player;
					m_playerInput = playerInput;
					m_playerAction = playerAction;
				}

				void CoolTimeOn();

				void CoolTimeOff();

				void CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr);

				void GetAnimationEvent(const std::string& animationEventName,
					const AnimationEventDataStr& animationEventData
					);

			private:
				IGameActor* m_player = nullptr;			//プレイヤーのポインタ
				CPlayerInput* m_playerInput = nullptr;	//プレイヤー入力クラス
				CPlayerAction* m_playerAction = nullptr;//プレイヤーアクションクラス
			};
		}
	}
}