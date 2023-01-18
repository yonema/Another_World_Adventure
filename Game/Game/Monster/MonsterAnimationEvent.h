#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;
	namespace nsMonster {

		class CMonster;

		namespace nsMonsterAI {

			class CMonsterAIController;
		}
	}

	namespace nsMonster {
		
		//前方宣言
		class CMonster;
		namespace nsMonsterAI {

			class CMonsterAIController;
		}

		//モンスターのアニメーションイベントクラス
		class CMonsterAnimationEvent : public nsUtils::SNoncopyable
		{
			//エイリアス宣言
			using AnimationEventDataStr = std::list<std::vector<std::string>>;

		public:
			void Init(CMonster* monster, nsMonsterAI::CMonsterAIController* monsterAIController) {

				//自身を取得。
				m_monster = monster;

				//AIコントローラーを取得。
				m_aiController = monsterAIController;
			}

			void GetAnimationEvent(const std::string& animationEventName,
				const AnimationEventDataStr& animationEventData
			);

			void CoolTimeOn();

			void CoolTimeOff();

			void CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr);

			void Release();

		private:
			CMonster* m_monster = nullptr;		//自身のポインタ
			nsMonsterAI::CMonsterAIController* m_aiController = nullptr;		//AIコントローラー
		};

	}
}