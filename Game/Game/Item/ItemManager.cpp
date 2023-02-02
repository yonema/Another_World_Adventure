#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "ItemManager.h"
#include "AllItemList.h"
#include "SelfItem.h"
#include "ThrowItem.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			const CVector3 kThrowAddPosition = { 0.0f,100.0f,0.0f };	//������ʒu�̏C�����Z���W
		}

		void CItemManager::UseItem() {

			//�A�C�e���̃��X�g����Ȃ�B
			if (!HasItem()) {
			
				//�A�C�e���g�p���ł��Ȃ��̂Ń��^�[���B
				return;
			}
			
			//�g�������A�C�e���̃C�e���[�^�����o���B
			auto itr = m_sItemList.begin();
			
			//�A�C�e���𐶐��B
			CItemBuilder itemBuilder;
			CItem* item = itemBuilder.CreateItemBase((*itr).name);

			//�A�C�e���̃N���X�����擾�B
			const type_info& id = typeid(*item);

			//���g�Ɏg���A�C�e����������B
			if (typeid(nsItem::CSelfItem) == id) {

				//�^�[�Q�b�g�����g�ɐݒ�B
				dynamic_cast<nsItem::CSelfItem*>(item)->SetTarget(m_target);
			}
			//������A�C�e����������B
			else if (typeid(nsItem::CThrowItem) == id) {

				//�����J�n�ʒu�Ɠ����������ݒ�B
				dynamic_cast<nsItem::CThrowItem*>(item)->SetStartPosition(m_target->GetPosition());
				dynamic_cast<nsItem::CThrowItem*>(item)->SetThrowDirection(m_target->GetForwardDirection());
			}

			//�A�C�e�����g�p�B
			item->Use();

			//�P�����B
			(*itr).hasNum--;

			//���̃A�C�e���̏�������0�ɂȂ�����B
			if ((*itr).hasNum == 0) {

				//���X�g����폜�B
				m_sItemList.erase(itr);
			}
		}

		void CItemManager::AddItem(std::string itemName, int getNum, bool back) {

			//���X�g�ɖ��O�����邩�����B
			bool isFound = CAllItemList::GetInstance()->IsFoundName(itemName);

			//���X�g�ɂȂ������B
			if (!isFound) {

				//�I���B
				return;
			}

			//�莝���̃A�C�e�������ɎQ�ƁB
			for (auto& itemList : m_sItemList) {

				//���O����v������B
				if (itemList.name == itemName) {

					//���ɓ����A�C�e���������Ă���̂ŏ����������Z�B
					itemList.hasNum += getNum;

					//�I���B
					return;
				}
			}

			//�����Ă��Ȃ������̂ŃA�C�e�����𐶐��B
			SHasItem item;
			item.name = itemName;	//���O
			item.hasNum = getNum;	//������


			if (back) {
				//�V���ɃA�C�e������ǉ��B
				m_sItemList.emplace_back(item);
			}
			else {
				//�V���ɃA�C�e������ǉ��B
				m_sItemList.emplace_front(item);
			}
		}
	}
}