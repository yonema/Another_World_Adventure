#include "YonemaEnginePreCompile.h"
#include "Item.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const char* const kItemModekFilePath = "Assets/Models/Item.fbx";	//�A�C�e�����f���̃t�@�C���p�X
			constexpr float kItemModelScale = 0.05f;	//�A�C�e�����f���̑傫��
			constexpr float kGetValidTime = 10.0f;		//�擾�L�����ԁi�b�j
		}

		bool CItem::Start() {

			//���f���f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kItemModekFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//�A�C�e�����f���𐶐��B
			m_itemModel = NewGO<CModelRenderer>();
			m_itemModel->Init(modelInitData);
			m_itemModel->SetScale(kItemModelScale);

			return true;
		}

		void CItem::OnDestroy() {

			//�j�������B

			if (m_itemModel != nullptr) {

				//�A�C�e�����f����j���B
				DeleteGO(m_itemModel);
				m_itemModel = nullptr;
			}
		}

		void CItem::Update(float deltaTime) {

			//�擾����Ă��Ȃ��Ȃ�B
			if (!m_isGet) {

				//�擾����i�������j
				{
					//�擾���ꂽ��B
#ifdef _DEBUG
					if (false)
#endif
					{

						//�擾�����ON�ɐݒ�B�iIGameObject�̏������~�����邽�߁A��������m_isGet�͕K�v�Ȃ���������Ȃ��j
						m_isGet = true;

						//�A�C�e�����f����j���B
						DeleteGO(m_itemModel);
						m_itemModel = nullptr;

						//���g�iIGameObject�j�̋@�\�͕K�v�Ȃ��Ȃ邽�ߒ�~�B
						this->Deactivate();


						//�I���B
						return;
					}
				}

				//��]�B
				m_rotation.AddRotationY(nsMath::YM_PIDIV2 * deltaTime);
				m_itemModel->SetRotation(m_rotation);

				//�擾�L�����ԃ^�C�}�[���X�V�B
				m_getValidTimer += deltaTime;

#ifdef _DEBUG
				////�擾�L�����Ԃ��߂�����B
				//if (m_getValidTimer > kGetValidTime) {
				//
				//	//�A�C�e�����f����j���B
				//	DeleteGO(m_itemModel);
				//	m_itemModel = nullptr;
				//
				//	//���g��j���B
				//	DeleteGO(this);
				//}
#endif
			}
		}

		void CItem::ExecuteFeature() {

			//���ʂ̃��X�g�����ɎQ�ƁB
			for (const auto& feature : m_featureList) {

				//���ʂ𔭓��B
				feature->Create();
			}
		}
	}
}