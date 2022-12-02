#include "YonemaEnginePreCompile.h"
#include "Item.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const char* const kItemModekFilePath = "Assets/Models/Item.fbx";	//アイテムモデルのファイルパス
			constexpr float kItemModelScale = 0.05f;	//アイテムモデルの大きさ
			constexpr float kGetValidTime = 10.0f;		//取得有効時間（秒）
		}

		bool CItem::Start() {

			//モデルデータを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kItemModekFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//アイテムモデルを生成。
			m_itemModel = NewGO<CModelRenderer>();
			m_itemModel->Init(modelInitData);
			m_itemModel->SetScale(kItemModelScale);

			return true;
		}

		void CItem::OnDestroy() {

			//破棄処理。

			if (m_itemModel != nullptr) {

				//アイテムモデルを破棄。
				DeleteGO(m_itemModel);
				m_itemModel = nullptr;
			}
		}

		void CItem::Update(float deltaTime) {

			//取得されていないなら。
			if (!m_isGet) {

				//取得判定（未実装）
				{
					//取得されたら。
#ifdef _DEBUG
					if (false)
#endif
					{

						//取得判定をONに設定。（IGameObjectの処理を停止させるため、そもそもm_isGetは必要ないかもしれない）
						m_isGet = true;

						//アイテムモデルを破棄。
						DeleteGO(m_itemModel);
						m_itemModel = nullptr;

						//自身（IGameObject）の機能は必要なくなるため停止。
						this->Deactivate();


						//終了。
						return;
					}
				}

				//回転。
				m_rotation.AddRotationY(nsMath::YM_PIDIV2 * deltaTime);
				m_itemModel->SetRotation(m_rotation);

				//取得有効時間タイマーを更新。
				m_getValidTimer += deltaTime;

#ifdef _DEBUG
				////取得有効時間を過ぎたら。
				//if (m_getValidTimer > kGetValidTime) {
				//
				//	//アイテムモデルを破棄。
				//	DeleteGO(m_itemModel);
				//	m_itemModel = nullptr;
				//
				//	//自身を破棄。
				//	DeleteGO(this);
				//}
#endif
			}
		}

		void CItem::ExecuteFeature() {

			//効果のリストを順に参照。
			for (const auto& feature : m_featureList) {

				//効果を発動。
				feature->Create();
			}
		}
	}
}