#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/FeatureManager.h"
#include "Item/ItemManager.h"
#include "Skill/PassiveSkillManager.h"

namespace nsAWA {

	bool IGameActor::Start() {

		//アイテム管理クラスを生成。
		m_itemManager = new nsItem::CItemManager;

		//パッシブスキル管理クラスを生成。
		m_passiveSkillManager = new nsSkill::CPassiveSkillManager;

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

		//パッシブスキルを更新。
		m_passiveSkillManager->UpdatePassiveSkill();

		//派生クラスを更新。
		UpdateActor(deltaTime);

		//ステータス変化を更新。
		m_featureManager->UpdateFeature(deltaTime);
	}
}