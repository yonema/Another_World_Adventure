#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;
	namespace nsMonster {

		class CMonster;

		namespace nsMonsterAI {

			class CMonsterAIController;
		}
	}

	namespace nsMonster {
		
		//�O���錾
		class CMonster;
		namespace nsMonsterAI {

			class CMonsterAIController;
		}

		//�����X�^�[�̃A�j���[�V�����C�x���g�N���X
		class CMonsterAnimationEvent : public nsUtils::SNoncopyable
		{
			//�G�C���A�X�錾
			using AnimationEventDataStr = std::list<std::vector<std::string>>;

		public:
			void Init(CMonster* monster, nsMonsterAI::CMonsterAIController* monsterAIController) {

				//���g���擾�B
				m_monster = monster;

				//AI�R���g���[���[���擾�B
				m_aiController = monsterAIController;
			}

			void GetAnimationEvent(const std::string& animationEventName,
				const AnimationEventDataStr& animationEventData
			);

			void CoolTimeOn();

			void CoolTimeOff();

			void CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr);

			void Release();

		private:
			CMonster* m_monster = nullptr;		//���g�̃|�C���^
			nsMonsterAI::CMonsterAIController* m_aiController = nullptr;		//AI�R���g���[���[
		};

	}
}