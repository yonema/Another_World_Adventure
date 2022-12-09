#pragma once
#include "Item.h"
#include "ItemCollision.h"

namespace nsAWA {

	namespace nsItem {

		//������A�C�e���N���X
		class CThrowItem : public CItem
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void Use()override final;

		private:
			void InitItemModel();

		public:
			void SetStartPosition(const CVector3& startPosition) {

				//�����J�n�̍��W���i�[�B
				m_startPosition = &startPosition;
			}

			void SetThrowDirection(const CVector3& throwDirection) {

				//������������i�[�B
				m_throwDirection = &throwDirection;
			}

		private:
			CModelRenderer* m_itemModel = nullptr;		//���f��
			CItemCollision m_collision;					//�����蔻��
			const CVector3* m_startPosition = nullptr;	//������ʒu
			const CVector3* m_throwDirection = nullptr;	//���������
		};
	}
}

