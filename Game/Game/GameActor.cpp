#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "AbnormalStatus/AbnormalStatus.h"

namespace nsAWA {

	void IGameActor::AddAbnormalStatus(nsAbnormalStatus::CAbnormalStatus* abnormalStatus) {

		//状態異常を付与。
		m_abnormalStatus.emplace_back(abnormalStatus);
	}

	void IGameActor::Update(float deltaTime) {

		//状態異常を更新。
		UpdateAbnormalStatus(deltaTime);

		//派生クラスを更新。
		UpdateActor(deltaTime);
	}

	void IGameActor::UpdateAbnormalStatus(float deltaTime) {

		//状態異常のリストのイテレータを順に参照。
		std::list<nsAbnormalStatus::CAbnormalStatus*>::iterator itr;
		for (itr = m_abnormalStatus.begin(); itr != m_abnormalStatus.end(); ) {

			//状態異常を更新。
			bool isDead = (*itr)->Update(deltaTime);

			//終了したか。
			if (isDead) {

				//この状態異常を破棄。
				itr = m_abnormalStatus.erase(itr);

				//破棄されたことにより、既に次のイテレータが入っているので移る処理をスキップ。
				continue;
			}

			//次のイテレータに移る。
			itr++;
		}


		
		//for (const auto& as : m_abnormalStatus) {

		//	//状態異常を更新。
		//	bool isDead = as->Update(deltaTime);

		//	//死んでいるなら破棄。
		//	if (isDead) {
		//		m_abnormalStatus.erase(as);
		//	}

		//	
		//}
	}
}