#include "YonemaEnginePreCompile.h"
#include "Feature.h"
#include "FeatureManager.h"
#include "AbnormalStatus/Paralysis.h"
#include "AbnormalStatus/Poison.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureManager::Release() {

			//効果を破棄。
			for (auto itr = m_feature.begin(); itr != m_feature.end(); ) {

				//破棄。
				if ((*itr) != nullptr) {
					delete (*itr);
				}

				itr = m_feature.erase(itr);

				continue;
			}
		}

		void CFeatureManager::UpdateFeature(float deltaTime) {

			//ステータス変化のリストのイテレータを順に参照。
			for (auto itr = m_feature.begin(); itr != m_feature.end(); ) {

				//ステータス変化の機能を更新。
				bool isDead = (*itr)->Update(deltaTime);

				//終了したか。
				if (isDead) {

					//このステータス変化を破棄。
					(*itr)->Release();
					itr = m_feature.erase(itr);

					//破棄されたことにより、既に次のイテレータが入っているので移る処理をスキップ。
					continue;
				}

				//次のイテレータに移る。
				itr++;
			}

			//ステータス変化の状態を更新。
			UpdateFeatureState();
		}

		void CFeatureManager::UpdateFeatureState() {

			//状態を初期化。
			m_isParalysis = false;
			m_isPoison = false;

			//ステータス変化のリストを順に参照。
			for (const auto& feature : m_feature) {

				//なんの状態か調べる。
				const type_info& id = typeid(*feature);

				//このクラスが麻痺クラスだったら。
				if (typeid(nsStatusChanger::CParalysis) == id) {

					//麻痺状態である。
					m_isParalysis = true;
				}
				else if (typeid(nsStatusChanger::CPoison) == id) {

					//毒状態である。
					m_isPoison = true;
				}
			}
		}

		bool CFeatureManager::CanUseActiveSkill() {

			//そもそも麻痺状態（やその他使用できない状態）ではない。
			if (!m_isParalysis) {

				//言うまでもなくアクティブスキルが使用できるので早期リターン。
				return true;
			}

			//ステータス変化のリストを順に参照。
			for (const auto& feature : m_feature) {

				//なんの状態か調べる。
				const type_info& id = typeid(*feature);

				//このクラスが麻痺クラスだったら。
				if (typeid(nsStatusChanger::CParalysis) == id) {

					//麻痺クラスにキャストし、アクティブスキルが使用可能かどうか調べる。
					bool canAttack = dynamic_cast<nsStatusChanger::CParalysis*>(feature)->CanUseActiveSkill();

					//この麻痺機能からアクティブスキルが使用できないと伝えられたら。
					if (!canAttack) {

						//こちらから呼び出し元にアクティブスキルが使用できないと伝える。
						return false;
					}
				}
			}

			//アクティブスキルが使用できる。
			return true;
		}
	}
}