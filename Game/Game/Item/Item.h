#pragma once
#include "AllItemList.h"

namespace nsAWA {

	//�O���錾
	class IGameActor;

	namespace nsFeature {

		class CFeature;
	}

	namespace nsItem {

		//�A�C�e���̃^�C�v
		enum class EnItemType {

			enSelf,			//���g�Ɏg�p
			enThrow,		//������

			enNum,			//��ސ�
			enNone = -1		//�ݒ�Ȃ�
		};

		//�A�C�e���N���X
		class CItem : public IGameObject
		{
		public:
			virtual void Use() = 0;

		public:
			void SetItemInfo(const SItemInfo& itemInfo) {

				//�A�C�e������ݒ�B
				m_itemInfo = itemInfo;
			}

			void SetItemName(std::string name) {

				//���O��ݒ�B
				m_itemInfo.name = name;
			}

			std::string GetItemName()const {

				//���O���擾�B
				return m_itemInfo.name;
			}

			void SetType(std::string type) {

				//�^�C�v��ݒ�B
				m_itemInfo.itemType = type;
			}
			
			std::string GetType()const {

				//�^�C�v���擾�B
				return m_itemInfo.itemType;
			}

			void SetTarget(IGameActor* target) {

				//�^�[�Q�b�g��ݒ�B
				m_target = target;
			}

		protected:
			void CreateFeature();

		private:
			SItemInfo m_itemInfo;	//�A�C�e�����
			IGameActor* m_target;
		};
	}
}

