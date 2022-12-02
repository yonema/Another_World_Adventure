#include "YonemaEnginePreCompile.h"
#include "ItemManager.h"
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		void CItemManager::UseItem() {

			//�A�C�e���̃��X�g����Ȃ�B
			if (!HasItem()) {

				//�A�C�e���g�p���ł��Ȃ��̂Ń��^�[���B
				return;
			}

			//�g�������A�C�e���̃C�e���[�^�����o���B
			auto itr = m_itemList.begin();
			itr += m_selectItemNum;

			//�A�C�e�����g�p�B
			(*itr)->Use();

			//�g�����A�C�e����j���B
			DeleteGO(*itr);

			//���X�g����A�C�e�����폜�B
			m_itemList.erase(itr);
		}
	}
}