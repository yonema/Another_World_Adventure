#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "PlayerAnimationEvent.h"
#include "PlayerAnimation.h"
#include "../PlayerAction.h"
#include "../../Skill/ActiveSkill.h"

#include "../../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr const wchar_t* const kPlayerAnimationCSVFilePath = L"Assets/CSV/Player/Test/Animation.csv";	//�v���C���[�̃A�j���[�V������CSV�t�@�C���p�X
				constexpr const wchar_t* const kPlayerAnimationEventCSVFilePath = L"Assets/CSV/Player/Test/AnimationEvent.csv";	//�v���C���[�̃A�j���[�V�����̃C�x���g��CSV�t�@�C���p�X
				constexpr const float kCanPlayerInput = 0.001f;	//���͂����肳���Œ�l
			}

			void CPlayerAnimation::Init(IGameActor* player, CPlayerInput* playerInput, CPlayerAction* playerAction) {

				//�A�j���[�V�����f�[�^��ǂݍ��ށB
				LoadAnimation();

				//�A�j���[�V�����C�x���g�N���X���������B
				m_animationEvent.Init(player, playerInput, playerAction, this);

				//���^�C�v�ɐݒ�B
				m_type = EnAnimType::enSword;

			}

			void CPlayerAnimation::SetPlayerModelAndAnimEvent(CModelRenderer* playerModel) {

				//�v���C���[���f����ݒ�B
				m_playerModel = playerModel;

				for (const auto& animData : m_animDataList) {
				
					//���̃A�j���[�V�����̃C�x���g����`����B
					m_playerModel->ReserveAnimationEventFuncArray(animData.animNum, static_cast<int>(animData.animationEvent.size()));
				
					//�A�j���[�V�����C�x���g�����ɎQ�ƁB
					for (const auto& animEventData : animData.animationEvent) {
					
						//�A�j���[�V�����C�x���g��ǉ��B
						m_playerModel->AddAnimationEventFunc(
							animData.animNum,
							[&]() {m_animationEvent.GetAnimationEvent(
								animEventData.eventName,
								animEventData.detailStr);
							}
						);
					}
				}
			}

			void CPlayerAnimation::Release() {

				//�f�[�^��j���B
				m_animDataList.clear();

				m_animFilePathArray.clear();
			}

			void CPlayerAnimation::Update(bool changeState, EnPlayerState playerState) {

				//�X�e�[�g�ɕύX�����������B
				if (changeState) {
					
					//�X�e�[�g�ɑΉ�����A�j���[�V�����𗬂��B
					PlayAnimation(playerState);
				}

				//�A�j���[�V�����C�x���g���X�V�B
				m_animationEvent.Update();
			}

			void CPlayerAnimation::PlayAnimation(EnPlayerState playerState) {

				//�X�e�[�g����Ή��A�j���[�V������index���擾�B
				const SAnimData& animationData = GetAnimationData(playerState);

				//�Ή�����A�j���[�V�������Ȃ��Ȃ�B
				if (animationData.animNum == -1) {

					//�Đ��ł��Ȃ��̂ő������^�[���B
					return;
				}
				else {

					//�Ή�����A�j���[�V�������Đ��B
					m_playerModel->PlayAnimationFromBeginning(
						animationData.animNum,
						animationData.speed,
						animationData.isLoopAnim
					);
				}
			}

			const SAnimData& CPlayerAnimation::GetAnimationData(EnPlayerState playerState) {

				std::string stateStr = "NoStr";

				//�v���C���[�̃^�C�v����A�j���[�V�����̐擪�������I������B
				switch (m_type) {

				case EnAnimType::enSword:

					stateStr = "Sword_";
					break;
				case EnAnimType::enAxe:

					stateStr = "Axe_";
					break;
				case EnAnimType::enWand:

					stateStr = "Wand_";
					break;
				}

				//�X�e�[�g�𕶎���ɕϊ����č����B
				switch (playerState) {

				case EnPlayerState::enIdle:
					stateStr += "Idle";
					break;
				case EnPlayerState::enWalk:
					stateStr += "Walk";
					break;
				case EnPlayerState::enRun:
					stateStr += "Run";
					break;
				case EnPlayerState::enStep:
					stateStr += "ForwardStep";
					break;
				case EnPlayerState::enWeakAttack_A:
					stateStr += "WeakAttack_A";
					break;
				case EnPlayerState::enWeakAttack_B:
					stateStr += "WeakAttack_B";
					break;
				case EnPlayerState::enWeakAttack_C:
					stateStr += "WeakAttack_C";
					break;
				case EnPlayerState::enStrongAttack:
					stateStr += "StrongAttack";
					break;
				case EnPlayerState::enUseActiveSkill:

					//�A�N�e�B�u�X�L���Ȃ�X�L���̖��O��ݒ�B
					SetActiveSkillName(stateStr);
					break;
				case EnPlayerState::enDamage:
					stateStr += "Damage";
					break;
				case EnPlayerState::enDeath:
					stateStr += "Death";
					break;
				case EnPlayerState::enGuard:
					stateStr += "Guard";
					break;
				case EnPlayerState::enUseItem:
					stateStr += "UseItem";
					break;
				case EnPlayerState::enStun:
					stateStr += "Stun";
					break;
				}

				//�A�j���[�V�������X�g����Ή�����A�j���[�V�����̔ԍ��������B
				for (const auto& animation : m_animDataList) {

					//�������O�̃A�j���[�V���������������B
					if (animation.animName == stateStr) {

						//���̃A�j���[�V���������^�[���B
						return animation;
					}
				}

				//������Ȃ������B
				std::string errMsg = "�Ή�����A�j���[�V������������܂���ł����B : ";
				errMsg += stateStr;
				nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errMsg).c_str());

				std::abort();
			}

			void CPlayerAnimation::SetActiveSkillName(std::string& name) {

				//�A�N�e�B�u�X�L���̖��O���擾�B
				if (m_activeSkill != nullptr) {

					if (m_activeSkill->GetType() == nsSkill::CActiveSkill::EnActiveSkillType::enMagic) {

						name = "Magic";

						//�I���B
						return;
					}

					//�A�j���[�V�������w�肷�邽�߁A�t�@�C���p�X���擾�B
					name = m_activeSkill->GetAnimationFilePath();

					//�I���B
					return;
				}
				else {
#ifdef _DEBUG
					//������Ȃ������B
					std::string errorMsg = "CPlayerAnimation : �A�N�e�B�u�X�L���̗\�񂪂���Ă��܂���B";

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

					std::abort();
#endif // _DEBUG
				}
			}

			void CPlayerAnimation::LoadAnimation() {

				//CSV�Ǘ��N���X�𐶐��B
				nsCSV::CCsvManager csvManager;

				//�v���C���[�A�j���[�V������CSV��ǂݍ��ށB
				csvManager.LoadCSV(kPlayerAnimationCSVFilePath);

				//�f�[�^�J�E���g���������B
				int dataIndex = 0;

				//�A�j���[�V�����f�[�^�̐��`�𐶐��B
				SAnimData animDataBase;

				//�A�j���[�V�����������o���B
				for (const auto& animData : csvManager.GetCsvData()) {

					//���o�����擾�B
					std::string titleData = animData[0];

					if (titleData == "*") {

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

					if (titleData == "NAME") {

						//�t�@�C���p�X���擾�A�ݒ�B
						std::string filePath = "Assets/Animations/Player/";
						filePath += animData[1];
						filePath += ".fbx";

						//�A�j���[�V�����̃t�@�C���p�X��z��ɒǉ��B
						m_animFilePathArray.emplace_back(filePath);

						//�A�j���[�V�����̖��O���擾�B
						animDataBase.animName = animData[1];

						//�ԍ����擾�B
						animDataBase.animNum = dataIndex;
					}

					if (titleData == "SPEED") {

						//�������擾�B
						animDataBase.speed = std::stof(animData[1]);
					}

					if (titleData == "LOOP") {

						//���[�v�t���O���擾�B
						animDataBase.isLoopAnim = animData[1] == "TRUE" ? true : false;
					}

					if (titleData == "EVENT") {

						SAnimationEventData animEventData;

						//�C�x���g���擾�B
						animEventData.eventName = animData[1];
						animEventData.detailStr = animData[2];

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
			}
		}
	}
}