#pragma once

namespace nsAWA {

	namespace nsMagic {

		//�O���錾
		class CMagicBase;

		//���@���X�g
		class CMagicList : nsUtils::SNoncopyable
		{
		public:
			//���@�X�L���̃f�[�^
			struct SMagicData {

				std::string name = "NoName";	//���O
				std::string magicType = "NoType";//���@�̎��
				std::list<std::vector<std::string>> featureList;	//���ʂ̃��X�g
			};

		public:
			static CMagicList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CMagicList* instance = new CMagicList;

				//�C���X�^���X���擾�B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadMagicList();


			const CMagicList::SMagicData& GetMagicData(const std::string& name)const;

			constexpr const auto& GetMagicList() const noexcept
			{
				//���@�X�L���̃��X�g���擾�B
				return m_magicList;
			}

		private:
			std::list<SMagicData> m_magicList;	//���@�X�L���̃��X�g
		};

		//���@�����N���X
		class CMagicBuilder : nsUtils::SNoncopyable {

		public:
			CMagicBase* CreateMagic(const std::string& magicName);
		};
	}
}

