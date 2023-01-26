#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/FeatureManager.h"
#include "Item/ItemManager.h"
#include "Skill/PassiveSkillManager.h"

namespace nsAWA {

	bool IGameActor::Start() {

		//アイテム管理クラスを生成。
		m_itemManager = new nsItem::CItemManager;

		//アイテム管理クラスを初期化。
		m_itemManager->Init(this);

		//パッシブスキル管理クラスを生成。
		m_passiveSkillManager = new nsSkill::CPassiveSkillManager;

		//効果管理クラスを生成。
		m_featureManager = new nsFeature::CFeatureManager;

		//派生クラスの開始処理。
		return StartSub();
	}

	void IGameActor::OnDestroy() {

		//破棄処理。

		if (m_itemManager != nullptr) {

			//アイテム管理クラスを破棄。
			delete m_itemManager;
		}

		if (m_passiveSkillManager != nullptr) {

			//パッシブスキル管理クラスを破棄。
			delete m_passiveSkillManager;
		}

		//派生クラスの破棄処理。
		OnDestroySub();
	}

	void IGameActor::UpdateForwardDirection() {

		//回転行列を計算。
		auto mRot = CMatrix::Identity();
		mRot.MakeRotationFromQuaternion(m_rotation);

		//前方向を設定。
		m_forwardDirection.x = mRot.m_fMat[2][0];
		m_forwardDirection.y = mRot.m_fMat[2][1];
		m_forwardDirection.z = mRot.m_fMat[2][2];

		//正規化。
		m_forwardDirection.Normalize();
	}

	void IGameActor::Update(float deltaTime) {

		//ヒットストップ中なら。
		if (m_hitStopTimer > FLT_EPSILON) {

			//タイマーを更新。
			m_hitStopTimer -= deltaTime;

			//モデルの座標を設定。
			m_modelRenderer->SetPosition(m_position + m_positionOffset);

			//終了。
			return;
		}
		else {

			//ヒットストップタイマーを初期化。
			m_hitStopTimer = 0.0f;

			//アニメーション速度を元に戻す。
			m_modelRenderer->SetAnimationSpeed(1.0f);
		}

		//前方向を更新。
		UpdateForwardDirection();

		//パッシブスキルを更新。
		m_passiveSkillManager->UpdatePassiveSkill();

		//派生クラスを更新。
		UpdateActor(deltaTime);

		//モデルの座標を設定。
		m_modelRenderer->SetPosition(m_position + m_positionOffset);

		//回転情報を設定。
		m_modelRenderer->SetRotation(m_rotation);

		//ステータス変化を更新。
		m_featureManager->UpdateFeature(deltaTime);
	}
}