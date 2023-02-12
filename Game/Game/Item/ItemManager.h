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

			void SetTatget(IGameActor* target) {

				//�^�[�Q�b�g��ݒ�B
				m_target = target;
			}

			const std::list<SHasItem>& GetItemList()const {

				//�A�C�e�����X�g���擾�B
				return m_sItemList;
			}

			void Init(IGameActor* target) {

				//�^�[�Q�b�g��ݒ�B
				m_target = target;
			}

			void NextItem() {

				//�擪�f�[�^���擾�B
				auto frontDataItr = m_sItemList.begin();
				std::string frontDataName = (*frontDataItr).name;
				int frontDataNum = (*frontDataItr).hasNum;

				//�擪�f�[�^��j���B
				m_sItemList.erase(frontDataItr);

				//�ŏI�Ƀf�[�^��ǉ��B
				AddItem(frontDataName, frontDataNum, true);
			}

			void BackItem() {

				//�ŏI�f�[�^���擾�B
				auto backDataItr = m_sItemList.end();
				backDataItr--;
				std::string backDataName = (*backDataItr).name;
				int backDataNum = (*backDataItr).hasNum;

				//�ŏI�f�[�^��j���B
				m_sItemList.erase(backDataItr);

				//�擪�Ƀf�[�^��ǉ��B
				AddItem(backDataName, backDataNum, false);
			}

			void UseItem();

#ifdef _DEBUG

			const std::string& GetItemName() {

				//�擪�̃A�C�e���̖��O���擾�B
				return ((*m_sItemList.begin()).name);
			}

			int GetItemNum() {

				//�擪�̃A�C�e���̐����擾�B
				return ((*m_sItemList.begin()).hasNum);
			}

			void GetAllItemName(std::list<std::string> nameVec)
			{
				// �擪����Ō�܂ł̃A�C�e���̖��O���擾
				for (auto forNum : m_sItemList) {
					nameVec.push_back(forNum.name);
				}
			}

#endif // _DEBUG


			void AddItem(std::string itemName, int getNum = 1, bool back = true);

			bool HasItem()const {

				//�T�C�Y��0���傫�����ǂ��������^�[���B
				return m_sItemList.size() > 0;
			}

		private:
			std::list<SHasItem> m_sItemList;	//�A�C�e�����X�g
			IGameActor* m_target = nullptr;		//�^�[�Q�b�g
		};
	}
}