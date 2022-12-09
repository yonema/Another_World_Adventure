#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;
	namespace nsItem {

		class CItem;
	}

	namespace nsItem {

		//�A�C�e���Ǘ��N���X
		class CItemManager : nsUtils::SNoncopyable
		{
		private:
			//�莝���̃A�C�e�����
			struct SHasItem {

				std::string name = "";	//���O
				int hasNum = 0;			//������
			};
		public:

			void Init(IGameActor* target) {

				//�^�[�Q�b�g��ݒ�B
				m_target = target;
			}

			void UseItem();

			void AddItem(std::string itemName, int getNum = 1);

			bool HasItem()const {

				//�T�C�Y��0���傫�����ǂ��������^�[���B
				return m_sItemList.size() > 0;
			}

		private:
			int m_selectItemNum = 0;			//�I�𒆂̃A�C�e���ԍ�
			std::list<SHasItem> m_sItemList;	//�A�C�e�����X�g
			IGameActor* m_target = nullptr;		//�^�[�Q�b�g
		};
	}
}