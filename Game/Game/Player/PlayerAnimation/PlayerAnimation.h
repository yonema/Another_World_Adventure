#pragma once
#include "PlayerAnimationEvent.h"

namespace nsAWA {

	//�O���錾
	namespace nsSkill {

		class CActiveSkill;
	}
	namespace nsPlayer {
		
		enum class EnPlayerState;
	}

	namespace nsPlayer {
		
		namespace nsPlayerAnimation {

			//�A�j���[�V�����̃^�C�v
			enum class EnAnimType {

				enSword,	//��
				enAxe,		//��
				enWand,		//��

				enNum,		//�^�C�v�̐�
				enNone		//�ݒ�Ȃ�

			};

			//�A�j���[�V�����f�[�^
			struct SAnimData {

				std::string animName = "NoName";	//�A�j���[�V������
				int animNum = -1;					//�A�j���[�V�����̔ԍ�
				float speed = 0.0f;							//���x
				bool isLoopAnim = false;					//���[�v�t���O
				std::vector<SAnimationEventData> animationEvent;			//�A�j���[�V�����C�x���g
			};

			//�v���C���[�A�j���[�V�����N���X
			class CPlayerAnimation : nsUtils::SNoncopyable
			{
			public:
				void Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction);

				void Release();

				const std::vector<std::string>& GetAnimFilePath()const {

					//�A�j���[�V�����̃t�@�C���p�X�����^�[���B
					return m_animFilePathArray;
				}

				void Update(bool changeState, EnPlayerState playerState);

				void SetPlayerModelAndAnimEvent(CModelRenderer* playerModel);

				void ReserveActiveSkillAnimation(nsSkill::CActiveSkill* activeSkill) {

					//�A�N�e�B�u�X�L���̃A�j���[�V�����Đ���\�񂷂邽�߁A�����擾�B
					m_activeSkill = activeSkill;
				}

			private:
				void PlayAnimation(EnPlayerState playerState);

				const SAnimData& GetAnimationData(EnPlayerState playerState);

				void LoadAnimation();

				const std::string& GetActiveSkillName()const;

			private:
				CModelRenderer* m_playerModel = nullptr;	//�v���C���[���f��
				EnAnimType m_type = EnAnimType::enNone;		//�A�j���[�V�����̃^�C�v
				CPlayerAnimationEvent m_animationEvent;		//�v���C���[�̃A�j���[�V�����C�x���g
				nsSkill::CActiveSkill* m_activeSkill = nullptr;	//�A�N�e�B�u�X�L���̃|�C���^

				std::vector<SAnimData> m_animDataList;	//�A�j���[�V�����f�[�^
				std::vector<std::string> m_animFilePathArray;	//�A�j���[�V�����̃t�@�C���p�X�̔z��
			};
		}
	}
}