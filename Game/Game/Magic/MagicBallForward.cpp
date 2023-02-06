#include "YonemaEnginePreCompile.h"
#include "MagicBallForward.h"
#include "MagicBallOne.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr short kMagicBallNum = 3;	//魔法の数
			constexpr float kInterval = 0.5f;	//魔法弾の間隔（s）
		}

		bool CMagicBallForward::Start() {

			//タイマーの間隔を設定。
			m_magicIntervalTimer = kInterval;

			//魔法弾を生成。
			CreateMagicBall();

			//成功。
			return true;
		}

		void CMagicBallForward::Update(float deltaTime) {

			//規定の数に達したら。
			if (m_createdNum == kMagicBallNum) {

				//自身を破棄。
				DeleteGO(this);
			}

			//タイマーを更新。
			m_magicIntervalTimer -= deltaTime;

			if (m_magicIntervalTimer < 0.0f) {

				//魔法弾を生成。
				CreateMagicBall();

				//タイマーを初期化。
				m_magicIntervalTimer = kInterval;
			}
		}

		void CMagicBallForward::CreateMagicBall() {

			//魔法弾を生成。
			CMagicBallOne* magicBall = NewGO<CMagicBallOne>();

			//情報を設定。
			magicBall->SetOwner(GetOwner());
			magicBall->SetMagicName(GetMagicName());
			magicBall->SetPosition(GetPosition());
			magicBall->SetMoveDirection(GetMoveDirection());
			magicBall->SetFeatureList(GetFeatureList());

			//生成したので数を加算。
			m_createdNum++;
		}
	}
}