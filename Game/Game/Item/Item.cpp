#include "YonemaEnginePreCompile.h"
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const char* const kItemModekFilePath = "Assets/Models/Item.fbx";
		}

		void CItem::Create() {

			//���f���f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kItemModekFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//�A�C�e�����f���𐶐��B
			m_itemModel = NewGO<CModelRenderer>();
			m_itemModel->Init(modelInitData);
			m_itemModel->SetScale(0.05f);
		}

		void CItem::Release() {

			//�A�C�e�����f����j���B
			DeleteGO(m_itemModel);
		}
	}
}