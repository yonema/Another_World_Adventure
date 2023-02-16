#pragma once

namespace nsAWA {

	namespace nsSound {

		//�T�E���h���X�g
		class CSoundList : nsUtils::SNoncopyable
		{
		public:
			//�T�E���h�f�[�^
			struct SSoundData {

				std::string name = "NoName";	//���O
				std::string type = "NoType";	//��ށiBGM,SE�j
				bool isLoop = false;			//���[�v�t���O
				float volume = 1.0f;			//����
			};

		public:
			static CSoundList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CSoundList* instance = new CSoundList;
				
				//�C���X�^���X���擾�B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadSoundList();

			const SSoundData& GetSoundData(const std::string& soundName)const;

		private:
			std::list<SSoundData> m_soundList;	//�T�E���h���X�g
		};

		//�T�E���h�����N���X�B
		class CSoundBuilder : nsUtils::SNoncopyable {

		public:
			CSoundPlayer* Create(const std::string& soundName);

		};
	}
}