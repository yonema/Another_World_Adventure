#pragma once
#include "../GameActor.h"

namespace nsAWA {

	namespace nsMonster {

		//�����X�^�[���
		struct SMonsterInfo {

			const char* name;						//�����X�^�[��
			const char* modelFilePath = nullptr;	//���f���̃t�@�C���p�X
		};

		//�����X�^�[�N���X
		class CMonster : public CGameActor
		{
		public:
			static const char* const m_kObjName_Monster;		//�����X�^�[�N���X�̖��O
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void Create(const SMonsterInfo& monsterInfo);

		private:
			void CreateMonsterModel(const SMonsterInfo& monsterInfo);
		private:
			const char* m_name = nullptr;
			CModelRenderer* m_modelRenderer = nullptr;	//���f��
		};
	}
}

