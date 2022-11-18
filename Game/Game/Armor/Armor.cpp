#include "YonemaEnginePreCompile.h"
#include "Armor.h"

namespace nsAWA {

	namespace nsArmor {

		void CArmor::Create(const SArmorInfo& armorInfo, const char* modelFilePath) {

			//防具モデルを生成。
			CreateModel(modelFilePath);

			//防具情報を設定。
			m_info = armorInfo;
		}

		void CArmor::Release() {

			//防具モデルを破棄。
			DeleteGO(m_modelRenderer);

			//自身を破棄。
			delete this;
		}

		void CArmor::CreateModel(const char* modelFilePath) {

			//防具モデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//防具モデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = modelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//防具モデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CArmor* CArmorBuilder::Create(const SArmorInfo& armorInfo, const char* modelFilePath) {

			//防具を生成。
			CArmor* armor = new CArmor;
			armor->Create(armorInfo, modelFilePath);

			//生成された防具を返す。
			return armor;
		}
	}
}