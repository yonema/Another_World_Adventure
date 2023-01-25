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

	void IGameActor::Update(float deltaTime) {

		//ヒットストップ中なら。
		if (m_hitStopTimer > FLT_EPSILON) {

			//タイマーを更新。
			m_hitStopTimer -= deltaTime;

			//終了。
			return;
		}
		else {

			//ヒットストップタイマーを初期化。
			m_hitStopTimer = 0.0f;

			//アニメーション速度を元に戻す。
			m_modelRenderer->SetAnimationSpeed(1.0f);
		}

		//パッシブスキルを更新。
		m_passiveSkillManager->UpdatePassiveSkill();

		//派生クラスを更新。
		UpdateActor(deltaTime);

		//ステータス変化を更新。
		m_featureManager->UpdateFeature(deltaTime);
	}
}