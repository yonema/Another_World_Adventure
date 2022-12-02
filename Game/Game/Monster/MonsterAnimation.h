#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsMonster {

		enum class EnMonsterState;
		enum class EnMonsterList;
	}

	namespace nsMonster {

		//�����X�^�[�A�j���[�V�����N���X
		class CMonsterAnimation : nsUtils::SNoncopyable
		{
		public:
			void Init(CModelRenderer* monsterModel, EnMonsterList monster);

			void Update(bool changeState, EnMonsterState state);

		private:
			void PlayAnimation(EnMonsterState state);

		private:
			EnMonsterList m_monster = static_cast<EnMonsterList>(-1);	//���̃����X�^�[��
			CModelRenderer* m_monsterModel = nullptr;	//�����X�^�[�̃��f��
		};
	}
}

