#include "YonemaEnginePreCompile.h"
#include "CreateTrigger.h"
#include "Feature/FeatureBuilder.h"
#include "GameActorCollider.h"
#include "GameActor.h"

namespace nsAWA {

	namespace {

		constexpr float kTriggerDurationTimer = 0.5f;	//トリガーの持続時間
	}

	void CCreateTrigger::Create(
		IGameActor* creator,
		std::list<std::vector<std::string>> triggerMaterial,
		const CVector3& position,
		const CVector3& forwardDirection
	) {
		//生成者を設定。
		m_creator = creator;

		//トリガー情報を設定。
		for (auto& material : triggerMaterial) {

			if (material[0] == "SIZE") {

				if (material[1] == "Small") {

					m_triggerInfo.size = 3.0f;
				}
				else if (material[1] == "Medium") {

					m_triggerInfo.size = 5.0f;
				}
				else if (material[1] == "Large") {

					m_triggerInfo.size = 10.0f;
				}
			}

			if (material[0] == "POSITION") {

				m_triggerInfo.position.x += stof(material[1]);
				m_triggerInfo.position.y += stof(material[2]);
				m_triggerInfo.position.z += stof(material[3]);
			}

			if (material[0] == "FEATURE") {

				material.erase(material.begin());

				m_triggerInfo.m_featureList.emplace_back(material);
			}
		}

		//前方向を取得。
		CVector3 triggerForward = forwardDirection;
		triggerForward.y = 0.0f;
		triggerForward.Normalize();

		//角度を求める。
		float angle = atan2(-forwardDirection.x, forwardDirection.z);

		//前方向に座標が設定されるように回転して修正。
		CQuaternion rot = CQuaternion::Identity();
		rot.SetRotationY(-angle);
		rot.Apply(m_triggerInfo.position);

		//トリガーを生成。
		m_trigger.InitAsBox({ m_triggerInfo.size ,m_triggerInfo.size ,m_triggerInfo.size },
			position + m_triggerInfo.position,
			EnPhysicsAttributes::enPlayerAttack
		);

		//回転を設定。
		m_trigger.SetRotation(rot);

		// TriggerEnterのコールバック関数を設定。
		m_trigger.SetOnTriggerEnterFunc(
			[&](CExtendedDataForRigidActor* otherData) {OnTriggerEnter(otherData); });

		//持続時間を設定。
		m_triggerDurationTime = kTriggerDurationTimer;
	}

	void CCreateTrigger::OnDestroy() {

		//トリガーを破棄。
		m_trigger.Release();
	}

	void CCreateTrigger::Update(float deltaTime) {

		//タイマーを更新。
		m_triggerDurationTime -= deltaTime;

		//タイマーが0になったら。
		if (m_triggerDurationTime <= 0.0f) {

			//自身を削除。
			DeleteGO(this);
		}
	}

	void CCreateTrigger::OnTriggerEnter(CExtendedDataForRigidActor* otherData) {

		//トリガーに入ったオブジェクトがIGameActorのコライダーかどうか調べる。
		auto rGameActorCollider = otherData->GetOwner<CGameActorCollider>();

		//自身のコライダーに入ったなら。
		if (rGameActorCollider == m_creator->GetGameActorCollider()) {

			//終了。
			return;
		}

		//IGameActorのコライダーだったら。
		if (rGameActorCollider != nullptr) {

			//効果を生成。
			nsFeature::CFeatureBuilder featureBuilder;
			featureBuilder.CreateFeature(m_creator, rGameActorCollider->GetGameActor(), m_triggerInfo.m_featureList);
		}
	}
}