#pragma once
#include "PlayerAnimationEvent.h"

namespace nsAWA {

	namespace nsPlayer {

		//�O���錾
		enum class EnPlayerState;
		namespace nsPlayerAnimation {

			class CPlayerAnimationBase;
		}
		
		namespace nsPlayerAnimation {

			//�v���C���[�A�j���[�V����
			class CPlayerAnimation : nsUtils::SNoncopyable
			{
				//�A�j���[�V�����̃^�C�v
				enum class EnAnimType {

					enSword,	//��
					enAxe,		//��
					enWand,		//��

					enNum,		//�^�C�v�̐�
					enNone		//�ݒ�Ȃ�
				};

			public:
				//�A�j���[�V�����̖��O�i�S�āj
				enum class EnAnimName {

					enSword_Idle,	//���ҋ@
					enSword_Walk,	//������
					enSword_Dash,	//������
					enSword_WeakAttack_A,	//����U��A
					enSword_StrongAttack,	//�����U��
					enSword_Damage,	//����e
					enSword_Death,	//�����S
					enSword_Guard,	//���K�[�h
					enSword_UseItem,	//���A�C�e���g�p
					enSword_Stun,	//���X�^��

					enNum,			//�A�j���[�V������
					enNone			//���O�Ȃ�
				};
			private:

				//�A�j���[�V�������
				enum class EnAnimInfo {

					enFilePath,			//�t�@�C���p�X
					enSpeed,			//���x
					enLoopFlag,			//���[�v�t���O
					enAnimationEvent	//�A�j���[�V�����C�x���g
				};

				//�A�j���[�V�����f�[�^
				struct SAnimData {

					EnAnimName animName = EnAnimName::enNone;	//�A�j���[�V�����̔ԍ�
					float speed = 0.0f;							//���x
					bool enLoopFlag = false;					//���[�v�t���O
					std::list<std::string> animationEvent;		//�A�j���[�V�����C�x���g
				};
			public:
				void Init(CPlayerInput* playerInput);

				std::string* GetAnimFilePath()const {

					//�A�j���[�V�����̃t�@�C���p�X�����^�[���B
					return m_animFilePaths;
				}

				void Update(bool changeState, EnPlayerState playerState);

				void SetPlayerModelAndAnimEvent(CModelRenderer* playerModel);

				void Release();

			private:
				void PlayAnimation(EnPlayerState playerState);

				void LoadAnimation();

			private:
				static std::string m_animFilePaths[static_cast<int>(EnAnimName::enNum)];		//�A�j���[�V�����̃t�@�C���p�X

				CModelRenderer* m_playerModel = nullptr;	//�v���C���[���f��
				EnAnimType m_type = EnAnimType::enNone;		//�A�j���[�V�����̃^�C�v
				CPlayerAnimationBase* m_playerAnimation[static_cast<int>(EnAnimType::enNum)] = { nullptr };		//�e�A�j���[�V����
				CPlayerAnimationEvent m_animationEvent;		//�v���C���[�̃A�j���[�V�����C�x���g

				std::vector<SAnimData> m_animDataList;	//�A�j���[�V�����f�[�^
			};
		}
	}
}