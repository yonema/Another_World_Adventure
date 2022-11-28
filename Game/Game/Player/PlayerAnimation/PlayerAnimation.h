#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//�G�C���A�X�錾
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
					//enAxe_Idle,	//���ҋ@
					//enWand_Idle,	//���ҋ@

					enNum			//�A�j���[�V������
				};

				void Init();

				const char* GetAnimFilePath()const {

					//�A�j���[�V�����̃t�@�C���p�X�����^�[���B
					return *m_kAnimFilePaths;
				}

				void UpdateAnimation(EnPlayerState playerState);

				void SetPlayerModel(CModelRenderer* playerModel) {

					//�v���C���[���f����ݒ�B
					m_playerModel = playerModel;
				}

				void Release();
			private:
				static const char* m_kAnimFilePaths[static_cast<int>(EnAnimName::enNum)];		//�A�j���[�V�����̃t�@�C���p�X

				CModelRenderer* m_playerModel = nullptr;	//�v���C���[���f��
				EnAnimType m_type = EnAnimType::enNone;		//�A�j���[�V�����̃^�C�v
				CPlayerAnimationBase* m_playerAnimation[static_cast<int>(EnAnimType::enNum)] = { nullptr };		//�e�A�j���[�V����
			};
		}
	}
}