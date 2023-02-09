#include "YonemaEnginePreCompile.h"
#include "ObservablePlayer.h"
#include "PlayerObserver.h"
#include "../Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			void CObservablePlayer::AddObserver(CPlayerObserver* observer) {

				//�I�u�U�[�o�[��ǉ��B
				m_observerList.emplace_back(observer);

				//�������B
				observer->Init(this);
			}

			void CObservablePlayer::ReleaseObserver() {

				//�j�����������s�B
				for (auto itr = m_observerList.begin(); itr != m_observerList.end(); ) {

					//�j���B
					(*itr)->Release();
					itr = m_observerList.erase(itr);

					//�j�����ꂽ���Ƃɂ��A���Ɏ��̃C�e���[�^�������Ă���̂ňڂ鏈�����X�L�b�v�B
					continue;
				}
			}

			void CObservablePlayer::NotifyObserver() {

				//�e�I�u�U�[�o�[�ɒʒm�B
				for (const auto& observer : m_observerList) {

					//�X�V�B
					observer->Update(this);
				}
			}

			/*------�ȉ��I�u�U�[�o�[�ɒ񋟂���֐�------*/

			int CObservablePlayer::GetExp()const {

				//�o���l���擾�B
				return m_player->GetStatus()->GetExp();
			}

			void CObservablePlayer::SetLevel(int level) {

				//���x����ݒ�B
				m_player->GetStatus()->SetLevel(level);
			}

			int CObservablePlayer::GetLevel()const {

				//���x�����擾�B
				return m_player->GetStatus()->GetLevel();
			}
		}
	}
}