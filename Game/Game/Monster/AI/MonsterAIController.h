#pragma once
#include "MonsterAIBlackboard.h"

namespace nsAWA {

	namespace nsMonster {

		//前方宣言
		class CMonster;
		enum class EnMonsterState;
		namespace nsMonsterAI {

			class CAIPart;
		}

		namespace nsMonsterAI {

			//エイリアス宣言
			using AIPartsDataStr = std::list<std::vector<std::string>>;

			//モンスターAIコントローラークラス
			class CMonsterAIController : nsUtils::SNoncopyable
			{
			public:
				void Init(CMonster* owner);

				void Release();

				CAIPart* CreateAIPart(AIPartsDataStr& AIPartsData);

				void Update(float deltaTime);

			private:
				void UpdateForwardDirection();

			public:
				void SetPosition(const CVector3& position);

				const CVector3& GetPosition()const;

				void SetRotation(const CQuaternion& rotation);

				const CQuaternion& GetRotation()const;

				const CVector3& GetForwardDirection()const;

				float GetDeltaTimeRef()const {

					//デルタタイムを取得。
					return m_deltaTimeRef;
				}

				void SetState(const EnMonsterState& state);

				const EnMonsterState& GetState()const;

				void SetWaitNode(CAIPart* waitTask) {

					if (m_waitNode == nullptr) {

						//待機タスクを設定。
						m_waitNode = waitTask;
					}
				}

				void CoolTimeOn() {

					//クールタイム中にする。
					m_isCoolTime = true;
				}

				void CoolTimeOff() {

					//クールタイムを切る。
					m_isCoolTime = false;
				}

				void FindPlayer() {

					//プレイヤーを発見。
					m_blackboard.m_isfindingTarget = true;
				}

			private:
				CMonster* m_owner = nullptr;	//モンスター（自身）のポインタ
				SMonsterAIBlackboard m_blackboard;	//ブラックボード
				CAIPart* m_rootNode = nullptr;		//ルートノード
				CAIPart* m_waitNode = nullptr;		//待機タスク
				float m_deltaTimeRef = 0.0f;		//デルタタイム
				bool m_isCoolTime = false;			//クールタイム中？
			};
		}
	}
}