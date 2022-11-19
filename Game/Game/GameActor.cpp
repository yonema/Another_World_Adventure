#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "StatusChanger/StatusChanger.h"

namespace nsAWA {

	void IGameActor::AddStatusChanger(nsStatusChanger::CStatusChanger* statusChanger) {

		//ステータス変化を付与。
		m_statusChanger.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

		//ステータス変化を更新。
		UpdateStatusChanger(deltaTime);

		//派生クラスを更新。
		UpdateActor(deltaTime);
	}

	void IGameActor::UpdateStatusChanger(float deltaTime) {

		//ステータス変化のリストのイテレータを順に参照。
		std::list<nsStatusChanger::CStatusChanger*>::iterator itr;
		for (itr = m_statusChanger.begin(); itr != m_statusChanger.end(); ) {

			//ステータス変化を更新。
			bool isDead = (*itr)->Update(deltaTime);

			//終了したか。
			if (isDead) {

				//このステータス変化を破棄。
				itr = m_statusChanger.erase(itr);

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