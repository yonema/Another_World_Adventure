#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;

	namespace nsMonster {

		namespace nsMonsterAI {

			//ブラックボード
			//AIで使用する情報を記憶する。
			struct SMonsterAIBlackboard : nsUtils::SNoncopyable
			{
				IGameActor* m_gameActor = nullptr;	//ゲームアクターのポインタ
				CVector3 m_targetPosition = CVector3::Zero();		//目標の座標
				float m_waitTimer = 0.0f;		//待機時間
			};
		}
	}
}