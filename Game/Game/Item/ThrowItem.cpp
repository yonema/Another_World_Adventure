#include "YonemaEnginePreCompile.h"
#include "ThrowItem.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const char* const kItemModekFilePath = "Assets/Models/Item.fbx";	//アイテムモデルのファイルパス
			constexpr float kItemModelScale = 0.05f;	//アイテムモデルの大きさ
		}

		bool CThrowItem::Start() {

			return true;
		}

		void CThrowItem::OnDestroy() {

			//破棄処理。

			if (m_itemModel != nullptr) {

				//アイテムモデルを破棄。
				DeleteGO(m_itemModel);
				m_itemModel = nullptr;
			}

			//当たり判定を破棄。
			m_collision.Release();
		}

		void CThrowItem::Update(float deltaTime) {

			//投げたアイテムが何かに当たったら。
			if (m_collision.IsHit()) {

				//アイテムモデルを破棄。
				DeleteGO(m_itemModel);
				m_itemModel = nullptr;
			}

			//モデルが生成されているなら。
			if (m_itemModel != nullptr) {

				//モデルの座標を剛体の座標と同じに設定。
				m_itemModel->SetPosition(m_collision.GetPosition());
			}

			//当たり判定を更新。
			m_collision.Update(deltaTime);

			//当たり判定にHitしたアクターを順に参照。
			for (auto itr = m_collision.GetHitActorList()->begin(); itr != m_collision.GetHitActorList()->end();) {

				//効果の対象を設定。
				SetTarget(*itr);

				//効果を生成。
				CreateFeature();

				//イテレータを破棄。
				itr = m_collision.GetHitActorList()->erase(itr);

				//次へ。
				continue;
			}

			//全て終了したら。
			if (m_collision.IsEnd()) {

				//自身を破棄。
				DeleteGO(this);
			}
		}

		void CThrowItem::Use() {

			//投げ開始位置が指定されていないなら。
			if (m_startPosition == nullptr) {

				//投げることができないため、警告表示。
				nsGameWindow::MessageBoxWarning(L"投げ開始の位置が指定されていないため、アイテムが使用できません。");
				return;
			}

			//投げる方向が指定されていないなら。
			if (m_throwDirection == nullptr) {

				//投げることができないため、警告表示。
				nsGameWindow::MessageBoxWarning(L"投げる方向が指定されていないため、アイテムが使用できません。");
				return;
			}

			//アイテムモデルを生成。
			InitItemModel();

			//当たり判定を初期化。
			m_collision.Init(*m_startPosition);

			//アイテムを投げる。
			m_collision.Throw(*m_throwDirection);
		}

		void CThrowItem::InitItemModel() {

			//モデルデータを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kItemModekFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//アイテムモデルを生成。
			m_itemModel = NewGO<CModelRenderer>();
			m_itemModel->SetScale(kItemModelScale);
			m_itemModel->SetPosition(*m_startPosition);
			m_itemModel->Init(modelInitData);
		}
	}
}