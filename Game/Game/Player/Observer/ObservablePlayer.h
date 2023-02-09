#pragma once

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

				void AddObserver(CPlayerObserver* observer);

				void ReleaseObserver();

				void NotifyObserver();

			private:
				CPlayer* m_player = nullptr;				//�v���C���[
				std::list<CPlayerObserver*> m_observerList;	//�I�u�U�[�o�[�̃��X�g



			/*------�ȉ��I�u�U�[�o�[�ɒ񋟂���֐�------*/
			public:
				int GetExp()const;

				void SetLevel(int level);

				int GetLevel()const;
			};
		}
	}
}

