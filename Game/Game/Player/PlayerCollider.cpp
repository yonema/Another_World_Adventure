#include "YonemaEnginePreCompile.h"
#include "PlayerCollider.h"
#include "Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr float kPlayerTriggerBoxRadius = 2.0f;		//トリガーの半径
			constexpr float kPlayerTriggerBoxHeight = 4.0f;		//トリガーの高さ

			const CVector3 kPlayerTriggerBoxAddPosition = { 0.0f,7.0f,0.0f };		//トリガーに加算する座標
		}

		void CPlayerCollider::CreateCollider() {

			//プレイヤーのポインタを格納。
			m_player = dynamic_cast<CPlayer*>(m_gameActor);

			//座標を格納。
			m_position = &(m_player->GetPosition());

			//トリガーに設定する最終座標を定義。
			CVector3 finalPosition = *m_position;
			finalPosition += kPlayerTriggerBoxAddPosition;

			//トリガーに設定する回転を定義。
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisZ(), nsMath::YM_PIDIV2);

			//当たり判定を初期化。
			m_trigger.InitAsCapsule<CGameActorCollider>(
				this,
				kPlayerTriggerBoxRadius,
				kPlayerTriggerBoxHeight,
				finalPosition,
				EnPhysicsAttributes::enPlayer
			);

			//トリガーを回転。
			m_trigger.SetRotation(rot);
		}

		void CPlayerCollider::Update() {

			//トリガーに設定する最終座標を定義。
			CVector3 finalPosition;
			finalPosition = *m_position + kPlayerTriggerBoxAddPosition;

			//座標を設定。
			m_trigger.SetPosition(finalPosition);
		}
	}
}