#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsItem {

		class CItem;
	}

	namespace nsItem {

		//�A�C�e���Ǘ��N���X
		class CItemManager : nsUtils::SNoncopyable
		{
		public:
			void AddItem(nsItem::CItem* item) {

				//�A�C�e�����X�g�ɃA�C�e����ǉ��B
				m_itemList.emplace_back(item);
			}

			void UseItem();

			void AddSelectItemNum() {

				//���X�g����Ȃ�B
				if (!HasItem()) {

					//�I���B
					return;
				}

				//���̃A�C�e��������B
				m_selectItemNum++;

				//�A�C�e���̃��X�g�̃T�C�Y�ȏ�Ȃ�B
				if (m_selectItemNum >= m_itemList.size()) {

					//�ŏ��̃A�C�e��������B
					m_selectItemNum = 0;
				}
			}

			void SubSelectItemNum() {

				//���X�g����Ȃ�B
				if (!HasItem()) {

					//�I���B
					return;
				}

				//�O�̃A�C�e��������B
				m_selectItemNum--;

				//�}�C�i�X�l�ɂȂ��Ă�����B
				if (m_selectItemNum < 0) {

					//�Ō�̃A�C�e��������B
					m_selectItemNum = m_itemList.size() - 1;
				}
			}

			bool HasItem()const {

				//�A�C�e���������Ă��邩�ǂ�����Ԃ��B
				return m_itemList.size() != 0;
			}

		private:
			int m_selectItemNum = 0;			//�I�𒆂̃A�C�e���ԍ�
			std::vector<CItem*> m_itemList;		//�A�C�e�����X�g
		};
	}
}