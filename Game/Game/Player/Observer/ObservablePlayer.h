#pragma once
#include "PlayerObserver.h"

namespace nsAWA {

	namespace nsPlayer {

		//�O���錾
		class CPlayer;
		namespace nsObserver {

			class CPlayerObserver;
		}

		namespace nsObserver {

			//�I�u�U�[�o�[���Ď�����N���X
			class CObservablePlayer : nsUtils::SNoncopyable
			{
			public:
				void Init(CPlayer* player) {

					//�v���C���[���l���B
					m_player = player;
				}

				void AddObserver(CPlayerObserver* observer, EnObserverEvent observerEvent = EnObserverEvent::enNone);

				void ReleaseObserver();

				void NotifyObserver(EnObserverEvent observerEvent,const std::string& message = "");

				EnObserverEvent GetCarentEvent()const {

					//���݂̃C�x���g���擾�B
					return m_carentEvent;
				}

			private:
				CPlayer* m_player = nullptr;				//�v���C���[
				EnObserverEvent m_carentEvent = EnObserverEvent::enNone;	//���݂̃C�x���g
				std::list<CPlayerObserver*> m_observerList;	//�I�u�U�[�o�[�̃��X�g



			/*------�ȉ��I�u�U�[�o�[�ɒ񋟂���֐�------*/
			public:
				int GetExp()const;

				void SetLevel(int level);

				int GetLevel()const;

				const CVector3& GetPlayerPosition()const;

				void InputEnableBySystem();

				void InputDisableBySystem();

				void ProgressSlayQuest(const std::string& slayMonsterName);
			};
		}
	}
}

