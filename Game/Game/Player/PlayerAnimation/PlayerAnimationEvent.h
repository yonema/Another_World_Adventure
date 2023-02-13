#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;
	namespace nsPlayer {

		class CPlayerInput;
		class CPlayerAction;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//�G�C���A�X�錾
			using AnimationEventDataStr = std::list<std::vector<std::string>>;

			//�A�j���[�V�����C�x���g�f�[�^
			struct SAnimationEventData {
				
				std::string eventName = "NoName";					//�C�x���g��
				bool hasEventMaterial = false;						//�C�x���g�ɕK�v�ȍޗ�������H
				AnimationEventDataStr eventData;					//�C�x���g�ޗ�
			};
			//�v���C���[�A�j���[�V�����C�x���g�N���X
			class CPlayerAnimationEvent : nsUtils::SNoncopyable
			{
			public:
				void Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction, CPlayerAnimation* playerAnimation) {

					//�e�|�C���^���i�[�B
					m_player = player;
					m_playerInput = playerInput;
					m_playerAction = playerAction;
					m_playerAnimation = playerAnimation;
				}

				void Update();

				void CoolTimeOn();

				void CoolTimeOff();

				void InputEnable();

				void CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr);

				void MoveStart();

				void MoveEnd();

				void Move();

				void CreateMagic();

				void GetAnimationEvent(const std::string& animationEventName,
					const AnimationEventDataStr& animationEventData
					);

			private:
				IGameActor* m_player = nullptr;			//�v���C���[�̃|�C���^
				CPlayerInput* m_playerInput = nullptr;	//�v���C���[���̓N���X
				CPlayerAction* m_playerAction = nullptr;//�v���C���[�A�N�V�����N���X
				CPlayerAnimation* m_playerAnimation = nullptr;//�v���C���[�A�j���[�V�����N���X
				bool m_isMoving = false;				//�C�x���g�ɂ���Ĉړ����Ă���H
				CVector3 m_playerMoveInput = CVector3::Zero();	//�v���C���[�̓��͕���
			};
		}
	}
}