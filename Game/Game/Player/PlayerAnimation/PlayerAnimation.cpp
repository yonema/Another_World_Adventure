#include "YonemaEnginePreCompile.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"

#include "../../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr const wchar_t* const kPlayerAnimationCSVFilePath = L"Assets/CSV/Animation.csv";	//�v���C���[�̃A�j���[�V������CSV�t�@�C���p�X
			}

			//�A�j���[�V�����̃t�@�C���p�X���`�B
			std::string CPlayerAnimation::
				m_animFilePaths[static_cast<int>(EnAnimName::enNum)] = {};

			void CPlayerAnimation::Init(CPlayerInput* playerInput) {

				//�A�j���[�V�����f�[�^��ǂݍ��ށB
				LoadAnimation();

				//�e�A�j���[�V���������蓖�Ă�B
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;

				//�A�j���[�V�����C�x���g�N���X���������B
				m_animationEvent.Init(playerInput);
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
					m_playerModel->ReserveAnimationEventFuncArray(static_cast<int>(animData.animName), animData.animationEvent.size());

					//�A�j���[�V�����C�x���g�����ɎQ�ƁB
					for (const auto& animEventName : animData.animationEvent) {
					
						//�A�j���[�V�����C�x���g�����ɎQ�ƁB
						m_playerModel->AddAnimationEventFunc(
							static_cast<unsigned int>(animData.animName),
							[&]() {m_animationEvent.GetAnimationEvent(animEventName); }
						);
					}
				}

				//m_playerModel->AddAnimationEventFunc(
				//	static_cast<unsigned int>(EnAnimName::enSword_UseItem),
				//	[&]() {m_animationEvent.CoolTimeOff(); }
				//);
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

				//�A�j���[�V�����������o���B
				for (const auto& anim : csvManager.GetCsvData()) {

					//�A�j���[�V�����f�[�^�̐��`�𐶐��B
					SAnimData animData;

					//�t�@�C���p�X���擾�B
					m_animFilePaths[dataIndex] += "Assets/Animations/";
					m_animFilePaths[dataIndex] += anim[static_cast<int>(EnAnimInfo::enFilePath)];
					m_animFilePaths[dataIndex] += ".fbx";

					//�ԍ����擾�B
					animData.animName = static_cast<EnAnimName>(dataIndex);

					//���x���擾�B
					animData.speed = std::stof(anim[static_cast<int>(EnAnimInfo::enSpeed)]);

					//���[�v�t���O�̕�������擾�B
					std::string loopFlag = anim[static_cast<int>(EnAnimInfo::enLoopFlag)];

					//�����񂩂烋�[�v�t���O��ݒ�B
					if (loopFlag == "TRUE") {

						animData.enLoopFlag = true;
					}
					else if (loopFlag == "FALSE") {

						animData.enLoopFlag = false;
					}
					else {
						nsGameWindow::MessageBoxError(L"�A�j���[�V�����̃��[�v��񂪐���������܂���B");
					}

					//�A�j���[�V�����C�x���g�����i�[�B
					for (int animationEvent = static_cast<int>(EnAnimInfo::enAnimationEvent); animationEvent < anim.size(); animationEvent++) {

						//���X�g�ɒǉ��B
						animData.animationEvent.emplace_back(anim[animationEvent]);
					}

					//�f�[�^���i�[�B
					m_animDataList.emplace_back(animData);

					//�f�[�^�J�E���g��i�߂�B
					dataIndex++;
				}
			}
		}
	}
}