#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//�O���錾
		namespace nsObserver {

			class CObservablePlayer;
		}

		namespace nsObserver {

			//�I�u�U�[�o�[�̃C�x���g
			enum class EnObserverEvent {

				enWin,	//���������Ƃ�
				enInputEnable,	//�v���C���[�̓��͂��󂯕t����
				enInputDisable,//�v���C���[�̓��͂��󂯕t���Ȃ�

				enNone = -1	//�ݒ�Ȃ�
			};

			//�ʒm�̒��ۃN���X
			class CPlayerObserver : nsUtils::SNoncopyable
			{
			public:
				void Init(CObservablePlayer* observablePlayer, EnObserverEvent observerEvent) {

					//�C�x���g���ݒ肳��Ă�����B
					if (observerEvent != EnObserverEvent::enNone) {
						//�C�x���g��ǉ��B
						AddEvent(observerEvent);
					}

					//�h���N���X���������B
					InitSub(observablePlayer);
				}

				virtual void InitSub(CObservablePlayer* observablePlayer) {};

				void Release() {

					//�h���N���X�̔j�����������s�B
					ReleaseSub();

					//���g��j���B
					delete this;
				}

				virtual void ReleaseSub() {};

				virtual void Update(CObservablePlayer* observablePlayer) = 0;

				void AddEvent(EnObserverEvent observerEvent) {

					//�C�x���g��ǉ��B
					m_observerEventList.emplace_back(observerEvent);
				}

				std::list<EnObserverEvent> GetEventList()const {

					//�C�x���g���X�g���擾�B
					return m_observerEventList;
				}

			private:
				std::list<EnObserverEvent> m_observerEventList;	//�I�u�U�[�o�[�̃C�x���g���X�g
			};
		}
	}
}