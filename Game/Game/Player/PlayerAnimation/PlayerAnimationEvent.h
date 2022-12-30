#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayerInput;
		class CPlayerAction;
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
				void Init(CPlayerInput* playerInput, CPlayerAction* playerAction) {

					//�e�|�C���^���i�[�B
					m_playerInput = playerInput;
					m_playerAction = playerAction;
				}

				void CoolTimeOn();

				void CoolTimeOff();

				void CreateTrigger(const AnimationEventDataStr& animEventDataStr);

				void GetAnimationEvent(const std::string& animationEventName,
					const AnimationEventDataStr& animationEventData
					);

			private:
				CPlayerInput* m_playerInput = nullptr;	//�v���C���[���̓N���X
				CPlayerAction* m_playerAction = nullptr;//�v���C���[�A�N�V�����N���X
			};
		}
	}
}