#pragma once
#include "MonsterAnimationEvent.h"

namespace nsAWA {

	//�O���錾
	namespace nsMonster {

		enum class EnMonsterState;
		enum class EnMonsterList;

		namespace nsMonsterAI {

			class CMonsterAIController;
		}
	}

	namespace nsMonster {

		//�G�C���A�X�錾
		using AnimationEventDataStr = std::list<std::vector<std::string>>;

		//�A�j���[�V�����C�x���g�f�[�^
		struct SAnimationEventData {

			std::string eventName = "NoName";					//�C�x���g��
			bool hasEventMaterial = false;						//�C�x���g�ɕK�v�ȍޗ�������H
			AnimationEventDataStr eventMaterial;				//�C�x���g�ޗ�
		};

		//�A�j���[�V�����f�[�^
		struct SAnimData {

			std::string animName = "NoName";	//�A�j���[�V������
			int animNum = -1;					//�A�j���[�V�����ԍ�
			float speed = 0.0f;							//���x
			bool isLoopAnim = false;					//���[�v����H
			std::vector<SAnimationEventData> animationEvent;			//�A�j���[�V�����C�x���g
		};

		//�����X�^�[�A�j���[�V�����N���X
		class CMonsterAnimation : nsUtils::SNoncopyable
		{
			
		public:
			void Init(
				CModelRenderer* monsterModel,
				const std::vector<SAnimData>& animDataList,
				const std::vector<std::string>& animFilePathArray
			);

			void Release();

			void InitAnimationEvent(CMonster* monster, nsMonsterAI::CMonsterAIController* aiController) {

				//�A�j���[�V�����C�x���g���������B
				m_animationEvent.Init(monster, aiController);
			}

			void Update(bool changeState, EnMonsterState state);

			void LoadAnimation(
				const std::string& monsterName,
				const wchar_t* monsterAnimationCSVFilePath,
				const wchar_t* monsterAnimationEventCSVFilePath
			);

		private:
			void PlayAnimation(EnMonsterState state);

			const SAnimData& GetAnimationData(EnMonsterState state)const;

		public:
			const std::vector<SAnimData>& GetAnimDataList()const {

				//�A�j���[�V�����f�[�^���擾�B
				return m_animDataList;
			}

			const std::vector<std::string>& GetAnimFilePathArray()const {

				//�A�j���[�V�����t�@�C���p�X���擾�B
				return m_animFilePathArray;
			}
		private:
			CModelRenderer* m_monsterModel = nullptr;	//�����X�^�[���f��
			CMonsterAnimationEvent m_animationEvent;	//�A�j���[�V�����C�x���g
			std::vector<SAnimData> m_animDataList;	//�A�j���[�V�����f�[�^
			std::vector<std::string> m_animFilePathArray;	//�A�j���[�V�����̃t�@�C���p�X�̔z��
			float m_hitStopTimer = 0.0f;	//�q�b�g�X�g�b�v�̎���
		};
	}
}

