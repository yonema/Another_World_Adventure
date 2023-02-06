#include "YonemaEnginePreCompile.h"
#include "MagicBallOne.h"
#include "../GameActorCollider.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr float kTriggerRadius = 5.0f;	//トリガーの半径
			constexpr float kDurationTime = 1.0f;	//持続時間
			constexpr float kMoveAmount = 130.0f;	//移動量
			constexpr float kAddPositionY = 10.0f;	//調整用加算座標
			constexpr float kAddPositionMoveDirection = 10.0f;	//調整用加算座標
		}

		bool CMagicBallOne::Start() {

			//座標を調整。
			CVector3 position = GetPosition();
			position.y += kAddPositionY;
			position += GetMoveDirection() * kAddPositionMoveDirection;

			//座標を設定。
			SetPosition(position);

			//当たり判定を初期化。
			m_trigger.InitAsSphere(kTriggerRadius, GetPosition());

			//TriggerEnterのコールバック関数を設定。
			m_trigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) {OnTriggerEnter(otherData); });

			//メインエフェクトを生成。
			m_mainEffect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Magics/";
			mainEffectFilePath += GetMagicName();
			mainEffectFilePath += "_Main.efkefc";

			//初期化。
			m_mainEffect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//メインエフェクトの座標を設定。
			m_mainEffect->SetPosition(position);

			//エフェクトを再生。
			m_mainEffect->Play();

			//持続時間を設定。
			m_durationTime = kDurationTime;

			//成功。
			return true;
		}

		void CMagicBallOne::OnDestroy() {

			if (m_mainEffect != nullptr) {

				m_mainEffect->Stop();
			}

			//エフェクトを破棄。
			DeleteGO(m_mainEffect);
			m_mainEffect = nullptr;

			//当たり判定を破棄。
			m_trigger.Release();
		}

		void CMagicBallOne::Update(float deltaTime) {

			//持続時間を更新。
			m_durationTime -= deltaTime;

			//持続時間が無くなったら。
			if (m_durationTime < 0.0f) {

				//自身を破棄。
				DeleteGO(this);
			}

			//座標を更新。
			CVector3 position = GetPosition();
			position += GetMoveDirection() * kMoveAmount * deltaTime;

			//座標を設定。
			SetPosition(position);
			m_mainEffect->SetPosition(GetPosition());
			m_trigger.SetPosition(GetPosition());
		}

		void CMagicBallOne::OnTriggerEnter(CExtendedDataForRigidActor* otherData) {

			//トリガーに入ったオブジェクトがIGameActorのコライダーかどうか調べる。
			auto rGameActorCollider = otherData->GetOwner<CGameActorCollider>();

			if (rGameActorCollider != nullptr) {

				//ターゲットに対して効果を発動。
				ExecuteFeature(rGameActorCollider->GetGameActor());
			}

			//エンドエフェクトを生成。
			CEffectPlayer* endEffect = NewGO<CEffectPlayer>();
			std::string endEffectFilePath = "Assets/Effects/Magics/";
			endEffectFilePath += GetMagicName();
			endEffectFilePath += "_End.efkefc";

			//初期化。
			endEffect->Init(nsUtils::GetWideStringFromString(endEffectFilePath).c_str());

			//再生。
			endEffect->Play();

			//座標を設定。
			endEffect->SetPosition(m_mainEffect->GetPosition());

			//変更を反映。
			endEffect->Update(0.0f);

			//終了時エフェクトを破棄。
			DeleteGO(endEffect);

			//当たり判定を無効化。
			m_trigger.Deactivate();

			//自身を破棄。
			DeleteGO(this);
		}
	}
}