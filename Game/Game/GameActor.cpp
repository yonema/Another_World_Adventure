#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "StatusChanger/StatusChanger.h"

namespace nsAWA {

	void IGameActor::AddStatusChanger(nsFeature::nsStatusChanger::CStatusChanger* statusChanger) {

		//ステータス変化を付与。
		m_statusChanger.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

		//ステータス変化を更新。
		UpdateStatusChangerAtStart(deltaTime);

		//派生クラスを更新。
		UpdateActor(deltaTime);

		//ステータス変化を更新。
		UpdateStatusChangerAtEnd(deltaTime);
	}

	void IGameActor::UpdateStatusChangerAtStart(float deltaTime) {

		//ステータス変化のリストのイテレータを順に参照。
		for (const auto& statusChanger : m_statusChanger) {

			//ステータス変化を更新。
			statusChanger->UpdateAtStart(deltaTime);
		}
	}

	void IGameActor::UpdateStatusChangerAtEnd(float deltaTime) {

		//ステータス変化のリストのイテレータを順に参照。
		std::list<nsFeature::nsStatusChanger::CStatusChanger*>::iterator itr;
		for (itr = m_statusChanger.begin(); itr != m_statusChanger.end(); ) {

			//ステータス変化を更新。
			bool isDead = (*itr)->UpdateAtEnd(deltaTime);

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
	}
}