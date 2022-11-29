#include "YonemaEnginePreCompile.h"
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const char* const kItemModekFilePath = "Assets/Models/Item.fbx";
		}

		void CItem::Create() {

			//モデルデータを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kItemModekFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//アイテムモデルを生成。
			m_itemModel = NewGO<CModelRenderer>();
			m_itemModel->Init(modelInitData);
			m_itemModel->SetScale(0.05f);
		}

		void CItem::Release() {

			//アイテムモデルを破棄。
			DeleteGO(m_itemModel);
		}
	}
}