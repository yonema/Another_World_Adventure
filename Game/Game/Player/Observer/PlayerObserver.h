#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//�O���錾
		namespace nsObserver {

			class CObservablePlayer;
		}

		namespace nsObserver {

			//�ʒm�̒��ۃN���X
			class CPlayerObserver : nsUtils::SNoncopyable
			{
			public:
				virtual void Init(CObservablePlayer* observablePlayer) {};

				void Release() {

					//�h���N���X�̔j�����������s�B
					ReleaseSub();

					//���g��j���B
					delete this;
				}

				virtual void ReleaseSub() {};

				virtual void Update(CObservablePlayer* observablePlayer) = 0;
			};
		}
	}
}