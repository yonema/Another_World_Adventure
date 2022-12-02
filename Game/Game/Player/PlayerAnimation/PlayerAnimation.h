#pragma once

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

				void Init();

				const char** GetAnimFilePath()const {

					//�A�j���[�V�����̃t�@�C���p�X�����^�[���B
					return m_kAnimFilePaths;
				}

				void Update(bool changeState, EnPlayerState playerState);

				void SetPlayerModel(CModelRenderer* playerModel) {

					//�v���C���[���f����ݒ�B
					m_playerModel = playerModel;
				}

				void Release();

			private:
				void PlayAnimation(EnPlayerState playerState);

			private:
				static const char* m_kAnimFilePaths[static_cast<int>(EnAnimName::enNum)];		//�A�j���[�V�����̃t�@�C���p�X

				CModelRenderer* m_playerModel = nullptr;	//�v���C���[���f��
				EnAnimType m_type = EnAnimType::enNone;		//�A�j���[�V�����̃^�C�v
				CPlayerAnimationBase* m_playerAnimation[static_cast<int>(EnAnimType::enNum)] = { nullptr };		//�e�A�j���[�V����
			};
		}
	}
}