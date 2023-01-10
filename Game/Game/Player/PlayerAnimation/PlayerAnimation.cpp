#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"

#include "../../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr const wchar_t* const kPlayerAnimationCSVFilePath = L"Assets/CSV/Animation.csv";	//�v���C���[�̃A�j���[�V������CSV�t�@�C���p�X
				constexpr const wchar_t* const kPlayerAnimationEventCSVFilePath = L"Assets/CSV/AnimationEvent.csv";	//�v���C���[�̃A�j���[�V�����̃C�x���g��CSV�t�@�C���p�X
				constexpr int kCSVTitleData = 0;		//CSV�f�[�^�̌��o�����B
			}

			//�A�j���[�V�����̃t�@�C���p�X���`�B
			std::string CPlayerAnimation::
				m_animFilePaths[static_cast<int>(EnAnimName::enNum)] = {};

			void CPlayerAnimation::Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction) {

				//�A�j���[�V�����f�[�^��ǂݍ��ށB
				LoadAnimation();

				//�e�A�j���[�V�������������B
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)]->Init(m_animDataList);

				//�A�j���[�V�����C�x���g�N���X���������B
				m_animationEvent.Init(player, playerInput, playerAction);
#ifdef _DEBUG
				//���^�C�v�ɐݒ�B
				m_type = EnAnimType::enSword;
#endif // _DEBUG

			}

			void CPlayerAnimation::SetPlayerModelAndAnimEvent(CModelRenderer* playerModel) {

				//�v���C���[���f����ݒ�B
				m_playerModel = playerModel;

				for (const auto& animData : m_animDataList) {
				
					//���̃A�j���[�V�����̃C�x���g����`����B
					m_playerModel->ReserveAnimationEventFuncArray(static_cast<int>(animData.animName), static_cast<int>(animData.animationEvent.size()));
				
					//�A�j���[�V�����C�x���g�����ɎQ�ƁB
					for (const auto& animEventData : animData.animationEvent) {
					
						//�A�j���[�V�����C�x���g��ǉ��B
						m_playerModel->AddAnimationEventFunc(
							static_cast<unsigned int>(animData.animName),
							[&]() {m_animationEvent.GetAnimationEvent(
								animEventData.eventName,
								animEventData.eventData);
							}
						);
					}
				}
			}

			void CPlayerAnimation::Release() {

			}

			void CPlayerAnimation::Update(bool changeState, EnPlayerState playerState) {

				//�X�e�[�g�ɕύX�����������B
				if (changeState) {
					
					//�X�e�[�g�ɑΉ�����A�j���[�V�����𗬂��B
					PlayAnimation(playerState);
				}
			}

			void CPlayerAnimation::PlayAnimation(EnPlayerState playerState) {

				//�A�j���[�V�����^�C�v����ǂ̃A�j���[�V�����N���X���g�������߂�B
				switch (m_type) {

					//���A�j���[�V�����N���X�B
				case EnAnimType::enSword:

					//�X�V�B
					m_playerAnimation[static_cast<int>(EnAnimType::enSword)]->UpdateAnimation(m_playerModel, playerState);
					break;
				}
			}

			void CPlayerAnimation::LoadAnimation() {

				//CSV�Ǘ��N���X�𐶐��B
				nsCSV::CCsvManager csvManager;

				//�v���C���[�A�j���[�V������CSV��ǂݍ��ށB
				csvManager.LoadCSV(kPlayerAnimationCSVFilePath);

				//�f�[�^�J�E���g���������B
				int dataIndex = 0;

				std::string topData = "";

				//�A�j���[�V�����f�[�^�̐��`�𐶐��B
				SAnimData animDataBase;

				//�A�j���[�V�����������o���B
				for (const auto& animData : csvManager.GetCsvData()) {

					if (animData[kCSVTitleData] == "*") {

						//�A�j���[�V�������̏I�[�Ȃ̂ŏ���ǉ��B

						//�f�[�^���i�[�B
						m_animDataList.emplace_back(animDataBase);

						//�f�[�^��i�߂�B
						dataIndex++;

						//�A�j���[�V�����f�[�^�̐��`���������B
						SAnimData clearData;
						animDataBase = clearData;

						//���ցB
						continue;
					}

					if (animData[kCSVTitleData] == "NAME") {

						//�t�@�C���p�X���擾�A�ݒ�B
						m_animFilePaths[dataIndex] += "Assets/Animations/Player/";
						m_animFilePaths[dataIndex] += animData[1];
						m_animFilePaths[dataIndex] += ".fbx";

						//�ԍ����擾�B
						animDataBase.animName = static_cast<EnAnimName>(dataIndex);
					}

					if (animData[kCSVTitleData] == "SPEED") {

						//�������擾�B
						animDataBase.speed = std::stof(animData[1]);
					}

					if (animData[kCSVTitleData] == "LOOP") {

						//���[�v�t���O���擾�B
						animDataBase.enLoopFlag = animData[1] == "TRUE" ? true : false;
					}

					if (animData[kCSVTitleData] == "EVENT") {

						SAnimationEventData animEventData;

						//�C�x���g���擾�B
						animEventData.eventName = animData[1];
						animEventData.hasEventMaterial = animData[2] == "TRUE" ? true : false;

						animDataBase.animationEvent.emplace_back(animEventData);
					}
				}

				//CSV�f�[�^���������B
				csvManager.ClearCSV();

				//�A�j���[�V�����C�x���g��CSV��ǂݍ��ށB
				csvManager.LoadCSV(kPlayerAnimationEventCSVFilePath);

				//�A�j���[�V�����C�x���g��ǉ����邽�߂̐��`���������B
				std::list<std::list<std::vector<std::string>>> animEventDataList;
				std::list<std::vector<std::string>> animEventData;

				//�A�j���[�V�����C�x���g�̃f�[�^�����X�g���B
				for (const auto& animEventStr : csvManager.GetCsvData()) {

					//��̃f�[�^�̏I�[�Ȃ�B
					if (animEventStr[0] == "*") {

						//���X�g�ɃC�x���g�f�[�^��ǉ��B
						animEventDataList.emplace_back(animEventData);

						//���`�̃f�[�^��j���B
						animEventData.clear();

						//���ցB
						continue;
					}

					//�C�x���g�̏���ǉ��B
					animEventData.emplace_back(animEventStr);
				}

				//�A�j���[�V�����f�[�^�����ɎQ�ƁB
				for (auto& animData : m_animDataList) {

					//�A�j���[�V�����C�x���g�����ɎQ�ƁB
					for (auto& animEvent : animData.animationEvent) {

						//�C�x���g��񂪕K�v�Ȃ��Ȃ�B
						if (!animEvent.hasEventMaterial) {

							//���̃C�x���g�ցB
							continue;
						}
						//�C�x���g�ɏ�񂪕K�v�Ȃ�B
						else {
							
							//�A�j���[�V�����C�x���g�f�[�^�̐擪�������o���B
							auto animEventDataItr = animEventDataList.begin();

							//�f�[�^���i�[�B
							animEvent.eventData = *animEventDataItr;

							//�擪����j���B
							animEventDataList.erase(animEventDataItr);
						}
					}
				}
			}
		}
	}
}