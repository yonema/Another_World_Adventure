#include "YonemaEnginePreCompile.h"
#include "MonsterCollider.h"
#include "Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr float kMonsterTriggerBoxRadius = 2.0f;		//トリガーの半径
			constexpr float kMonsterTriggerBoxHeight = 4.0f;		//トリガーの高さ

			const CVector3 kMonsterTriggerBoxAddPosition = { 0.0f,7.0f,0.0f };		//トリガーに加算する座標
		}

		void CMonsterCollider::CreateCollider() {

			//モンスターのポインタを格納。
			m_monster = dynamic_cast<CMonster*>(m_gameActor);

			//座標を格納。
			m_position = &(m_monster->GetPosition());

			//トリガーに設定する最終座標を定義。
			CVector3 finalPosition = *m_position;
			finalPosition += kMonsterTriggerBoxAddPosition;

			//トリガーに設定する回転を定義。
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisZ(), nsMath::YM_PIDIV2);

			//当たり判定を初期化。
			m_triggerBox.InitAsCapsule<CGameActorCollider>(
				this,
				kMonsterTriggerBoxRadius,
				kMonsterTriggerBoxHeight,
				finalPosition,
				EnPhysicsAttributes::enMonster
				);

			//トリガーを回転。
			m_triggerBox.SetRotation(rot);
		}

		void CMonsterCollider::Update() {

			//トリガーに設定する最終座標を定義。
			CVector3 finalPosition;
			finalPosition = *m_position + kMonsterTriggerBoxAddPosition;

			//座標を設定。
			m_triggerBox.SetPosition(finalPosition);
		}

		void CMonsterCollider::Release() {

			//当たり判定を破棄。
			m_triggerBox.Release();
		}
	}
}