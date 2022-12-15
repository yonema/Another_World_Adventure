#include "YonemaEnginePreCompile.h"
#include "ThrowItem.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const char* const kItemModekFilePath = "Assets/Models/Item.fbx";	//�A�C�e�����f���̃t�@�C���p�X
			constexpr float kItemModelScale = 0.05f;	//�A�C�e�����f���̑傫��
		}

		bool CThrowItem::Start() {

			return true;
		}

		void CThrowItem::OnDestroy() {

			//�j�������B

			if (m_itemModel != nullptr) {

				//�A�C�e�����f����j���B
				DeleteGO(m_itemModel);
				m_itemModel = nullptr;
			}

			//�����蔻���j���B
			m_collision.Release();
		}

		void CThrowItem::Update(float deltaTime) {

			//�������A�C�e���������ɓ���������B
			if (m_collision.IsHit()) {

				//�A�C�e�����f����j���B
				DeleteGO(m_itemModel);
				m_itemModel = nullptr;
			}

			//���f������������Ă���Ȃ�B
			if (m_itemModel != nullptr) {

				//���f���̍��W�����̂̍��W�Ɠ����ɐݒ�B
				m_itemModel->SetPosition(m_collision.GetPosition());
			}

			//�����蔻����X�V�B
			m_collision.Update(deltaTime);

			//�����蔻���Hit�����A�N�^�[�����ɎQ�ƁB
			for (auto itr = m_collision.GetHitActorList()->begin(); itr != m_collision.GetHitActorList()->end();) {

				//���ʂ̑Ώۂ�ݒ�B
				SetTarget(*itr);

				//���ʂ𐶐��B
				CreateFeature();

				//�C�e���[�^��j���B
				itr = m_collision.GetHitActorList()->erase(itr);

				//���ցB
				continue;
			}

			//�S�ďI��������B
			if (m_collision.IsEnd()) {

				//���g��j���B
				DeleteGO(this);
			}
		}

		void CThrowItem::Use() {

			//�����J�n�ʒu���w�肳��Ă��Ȃ��Ȃ�B
			if (m_startPosition == nullptr) {

				//�����邱�Ƃ��ł��Ȃ����߁A�x���\���B
				nsGameWindow::MessageBoxWarning(L"�����J�n�̈ʒu���w�肳��Ă��Ȃ����߁A�A�C�e�����g�p�ł��܂���B");
				return;
			}

			//������������w�肳��Ă��Ȃ��Ȃ�B
			if (m_throwDirection == nullptr) {

				//�����邱�Ƃ��ł��Ȃ����߁A�x���\���B
				nsGameWindow::MessageBoxWarning(L"������������w�肳��Ă��Ȃ����߁A�A�C�e�����g�p�ł��܂���B");
				return;
			}

			//�A�C�e�����f���𐶐��B
			InitItemModel();

			//�����蔻����������B
			m_collision.Init(*m_startPosition);

			//�A�C�e���𓊂���B
			m_collision.Throw(*m_throwDirection);
		}

		void CThrowItem::InitItemModel() {

			//���f���f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kItemModekFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//�A�C�e�����f���𐶐��B
			m_itemModel = NewGO<CModelRenderer>();
			m_itemModel->SetScale(kItemModelScale);
			m_itemModel->SetPosition(*m_startPosition);
			m_itemModel->Init(modelInitData);
		}
	}
}