#include "YonemaEnginePreCompile.h"
#include "ObservablePlayer.h"
#include "PlayerObserver.h"
#include "../Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			void CObservablePlayer::AddObserver(CPlayerObserver* observer, EnObserverEvent observerEvent) {

				//�I�u�U�[�o�[��ǉ��B
				m_observerList.emplace_back(observer);

				//�������B
				observer->Init(this, observerEvent);
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

			void CObservablePlayer::NotifyObserver(EnObserverEvent observerEvent,const std::string& message) {

				//�C�x���g���擾�B
				m_carentEvent = observerEvent;

				//�e�I�u�U�[�o�[�ɒʒm�B
				for (const auto& observer : m_observerList) {

					//�C�x���g���X�g�����ɎQ�ƁB
					for (auto observerEventData : observer->GetEventList()) {

						//�C�x���g����v������B
						if (observerEventData == observerEvent) {

							//�X�V�B
							observer->Update(this,message);

							//���̃I�u�U�[�o�[�͍X�V�����̂ŏI���B
							break;
						}
					}
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

			void CObservablePlayer::InputEnableBySystem() {

				//���͂ł����Ԃɂ���B
				m_player->InputEnableBySystem();
			}

			void CObservablePlayer::InputDisableBySystem() {

				//���͂ł��Ȃ���Ԃɂ���B
				m_player->InputDisableBySystem();
			}

			void CObservablePlayer::ProgressSlayQuest(const std::string& slayMonsterName)
			{
				//�����N�G�X�g��i�߂�
				m_player->ProgressSlayQuest(slayMonsterName);
			}

			const CVector3& CObservablePlayer::GetPlayerPosition()const {

				//�v���C���[�̍��W���擾�B
				return m_player->GetPosition();
			}
		}
	}
}