#include "YonemaEnginePreCompile.h"
#include "Armor.h"

namespace nsAWA {

	namespace nsArmor {

		void CArmor::Create(const SArmorInfo& armorInfo, const char* modelFilePath) {

			//�h��f���𐶐��B
			CreateModel(modelFilePath);

			//�h�����ݒ�B
			m_info = armorInfo;
		}

		void CArmor::Release() {

			//�h��f����j���B
			DeleteGO(m_modelRenderer);

			//���g��j���B
			delete this;
		}

		void CArmor::CreateModel(const char* modelFilePath) {

			//�h��f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�h��f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = modelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//�h��f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CArmor* CArmorBuilder::Create(const SArmorInfo& armorInfo, const char* modelFilePath) {

			//�h��𐶐��B
			CArmor* armor = new CArmor;
			armor->Create(armorInfo, modelFilePath);

			//�������ꂽ�h���Ԃ��B
			return armor;
		}
	}
}