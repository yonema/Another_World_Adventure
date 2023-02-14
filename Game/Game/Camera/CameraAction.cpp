#include "YonemaEnginePreCompile.h"
#include "CameraAction.h"
#include "../Player/Player.h"

namespace nsAWA {

	namespace nsCamera {

		namespace {

			const CVector3 kStartAddCameraVec = { 0.0f,10.0f,-30.0f };		//開始時点での加算ベクトル
			constexpr const float kRotationSpeed = 2.0f;					//回転速度
			constexpr const float kAddPlayerPosition = 10.0f;				//プレイヤーの胸あたりを見るための加算スカラー
			constexpr float kDirectionUpMax = -0.5f;						//カメラがどれくらい上を向けるか
			constexpr float kDirectionDownMax = 0.8f;						//カメラがどれくらい下を向けるか
		}

		void CCameraAction::Init(nsPlayer::CPlayer* player) {

			//プレイヤーのポインタを取得。
			m_player = player;

			//加算ベクトルを初期化。
			m_addCameraVec = kStartAddCameraVec;
		}

		void CCameraAction::Update() {

			//プレイヤーの座標を取得。
			CVector3 playerPosition = m_player->GetPosition();

			//プレイヤーの揺れとは反対にオフセットを設定。
			CVector3 cameraPositionOffset = m_player->GetPositionOffset();
			cameraPositionOffset *= -1.0f;

			//注視点を調整。
			playerPosition.y += kAddPlayerPosition;

			//注視点を設定。
			m_targetPosition = playerPosition + cameraPositionOffset;

			//視点を設定。
			m_position = m_targetPosition + m_addCameraVec;
		}

		void CCameraAction::Rotate(float rotateUp, float rotateRight) {

			//現在のの加算ベクトル情報を一時保存。
			CVector3 toCameraPosOld = m_addCameraVec;

			//Y軸周りの回転。
			CQuaternion qRotY;
			qRotY.SetRotationDeg(CVector3::AxisY(), kRotationSpeed * rotateRight);
			qRotY.Apply(m_addCameraVec);

			//X軸周りの回転。
			CVector3 axisX;
			axisX.Cross(CVector3::AxisY(), m_addCameraVec);
			axisX.Normalize();
			qRotY.SetRotationDeg(axisX, kRotationSpeed * rotateUp);
			qRotY.Apply(m_addCameraVec);

			//加算ベクトルの方向を求める。
			CVector3 toPosDir = m_addCameraVec;
			toPosDir.Normalize();

			//カメラ角度を修正。
			//角度上限を超えているなら回転させない。
			if (toPosDir.y < kDirectionUpMax) {
				//上方向。
				m_addCameraVec = toCameraPosOld;
			}
			else if (toPosDir.y > kDirectionDownMax) {
				//下方向。
				m_addCameraVec = toCameraPosOld;
			}

		}

	}
}