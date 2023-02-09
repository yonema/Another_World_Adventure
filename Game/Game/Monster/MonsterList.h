#pragma once
#include "MonsterAnimation.h"

namespace nsAWA {

	namespace nsMonster {

		//�O���錾
		class CMonster;
		struct SAnimData;

		//�����X�^�[�f�[�^
		struct SMonsterInitData {

			std::string name = "NoName";				//���O
			int dropExp = 0;							//�l���o���l��
			std::string modelFilePath = "NoFilePath";	//���f���̃t�@�C���p�X
			std::vector<std::string> animationFilePath;	//�A�j���[�V�����̃t�@�C���p�X�̃��X�g
			std::vector<SAnimData> animDataList;		//�A�j���[�V�����f�[�^
		};
		//�����X�^�[���X�g
		class CMonsterList : public nsUtils::SNoncopyable {

			
		public:
			static CMonsterList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CMonsterList* instance = new CMonsterList;

				//�C���X�^���X�����^�[���B
				return instance;
			}

			static void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void CreateMonsterList();

			CMonster* CreateMonster(const std::string& monsterName);

		private:
			void AddMonsterInitData(const SMonsterInitData& monsterData) {

				//�����X�^�[�f�[�^��ǉ��B
				m_monsterDataList.emplace_back(monsterData);
			}

		private:

			std::list<SMonsterInitData> m_monsterDataList;	//�����X�^�[�f�[�^�̃��X�g
		};
	}
}