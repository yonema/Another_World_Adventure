#include "YonemaEnginePreCompile.h"
#include "MagicBallSide.h"
#include "MagicBallOne.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr short kMagicBallNum = 3;	//魔法の数
			constexpr float kInterval = 15.0f;	//魔法弾の間隔
		}

		bool CMagicBallSide::Start() {

			//魔法の間隔の長さを求める。
			float magicIntervalLength = kInterval * (kMagicBallNum - 1);

			//全体の長さの半分の長さを求める。
			float magicIntervalLengthHalf = magicIntervalLength / 2.0f;

			//横方向を求める。
			CVector3 sideDirection = Cross(GetMoveDirection(), CVector3::AxisY());
			sideDirection.Normalize();

			//魔法の開始位置を設定。
			CVector3 startMagicPosition = GetPosition() - sideDirection * magicIntervalLengthHalf;

			//必要な数だけ魔法弾を生成。
			for (int magicNum = 0; magicNum < kMagicBallNum; magicNum++) {

				//魔法弾を生成。
				CMagicBallOne* magicBall = NewGO<CMagicBallOne>();

				//情報を設定。
				magicBall->SetOwner(GetOwner());
				magicBall->SetMagicName(GetMagicName());
				magicBall->SetPosition(startMagicPosition);
				magicBall->SetMoveDirection(GetMoveDirection());
				magicBall->SetFeatureList(GetFeatureList());

				//次の座標を調整。
				startMagicPosition += sideDirection * kInterval;
			}

			//生成が終わったので自身を破棄。
			DeleteGO(this);

			//成功。
			return true;
		}
	}
}