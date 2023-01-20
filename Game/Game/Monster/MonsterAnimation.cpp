#include "YonemaEnginePreCompile.h"
#include "Monster.h"
#include "MonsterAnimation.h"
#include "MonsterList.h"
#include "../CSV/CSVManager.h"
#include "../Utils/StringManipulation.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr int kCSVTitleData = 0;		//CSV�f�[�^�̌��o�����B
		}

		void CMonsterAnimation::Init(
			CModelRenderer* monsterModel,
			const std::vector<SAnimData>& animDataList,
			const std::vector<std::string>& animFilePathArray
		) {

			//�����X�^�[�̃��f���̃|�C���^���󂯎��B
			m_monsterModel = monsterModel;

			//�A�j���[�V�����f�[�^��ݒ�B
			m_animDataList = animDataList;

			//�A�j���[�V�����t�@�C���p�X��ݒ�B
			m_animFilePathArray = animFilePathArray;

			for (const auto& animData : m_animDataList) {

				//���̃A�j���[�V�����̃C�x���g����`����B
				m_monsterModel->ReserveAnimationEventFuncArray(static_cast<int>(animData.animNum), static_cast<int>(animData.animationEvent.size()));

				//�A�j���[�V�����C�x���g�����ɎQ�ƁB
				for (const auto& animEventData : animData.animationEvent) {

					//�A�j���[�V�����C�x���g��ǉ��B
					m_monsterModel->AddAnimationEventFunc(
						static_cast<unsigned int>(animData.animNum),
						[&]() {m_animationEvent.GetAnimationEvent(
							animEventData.eventName,
							animEventData.eventMaterial);
						}
					);
				}
			}
		}

		void CMonsterAnimation::Release() {

			//�f�[�^��j���B
			m_animDataList.clear();

			m_animFilePathArray.clear();
		}

		void CMonsterAnimation::Update(bool changeState, EnMonsterState state) {

			//�X�e�[�g�ɕύX����������B
			if (changeState) {

				//�X�e�[�g�ɑΉ�����A�j���[�V�������Đ��B
				PlayAnimation(state);
			}
		}

		void CMonsterAnimation::PlayAnimation(EnMonsterState state) {

			//�X�e�[�g����Ή��A�j���[�V������index���擾�B
			const SAnimData& animationData = GetAnimationData(state);
			
			//�Ή�����A�j���[�V�������Ȃ��Ȃ�B
			if (animationData.animNum == -1) {
			
				//�Đ��ł��Ȃ��̂ő������^�[���B
				return;
			}
			else {
			
				//�Ή�����A�j���[�V�������Đ��B
				m_monsterModel->PlayAnimationFromBeginning(
					animationData.animNum,
					animationData.speed,
					animationData.isLoopAnim
				);
			}
		}

		const SAnimData& CMonsterAnimation::GetAnimationData(EnMonsterState state)const {

			std::string stateStr = "NoStr";

			//�X�e�[�g�𕶎���ɕϊ��B
			switch (state) {

			case EnMonsterState::enIdle:
				stateStr = "Idle";
				break;
			case EnMonsterState::enWalk:
				stateStr = "Walk";
				break;
			case EnMonsterState::enRun:
				stateStr = "Run";
				break;
			case EnMonsterState::enBark:
				stateStr = "Bark";
				break;
			case EnMonsterState::enWeakAttack:
				stateStr = "WeakAttack";
				break;
			case EnMonsterState::enStrongAttack:
				stateStr = "StrongAttack";
				break;
			case EnMonsterState::enDamage:
				stateStr = "Damage";
				break;
			case EnMonsterState::enDeath:
				stateStr = "Death";
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

			//���ɏI�[�����^�[���B
			return *m_animDataList.end();
		}

		void CMonsterAnimation::LoadAnimation(
			const std::string& monsterName,
			const wchar_t* monsterAnimationCSVFilePath,
			const wchar_t* monsterAnimationEventCSVFilePath
		) {

			//CSV�Ǘ��N���X�𐶐��B
			nsCSV::CCsvManager csvManager;

			//�A�j���[�V������CSV��ǂݍ��ށB
			csvManager.LoadCSV(monsterAnimationCSVFilePath);

			//�f�[�^�J�E���g���������B
			int dataIndex = 0;

			//�A�j���[�V�����̃J�E���g�B
			int animNum = -1;						

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
					std::string filePath = "Assets/Animations/Monsters/";
					filePath = filePath + monsterName + "/";
					filePath = filePath + animData[1] + ".fbx";

					//�A�j���[�V�����̃t�@�C���p�X��z��ɒǉ��B
					m_animFilePathArray.emplace_back(filePath);

					//��؂蕶������A�j���[�V�����̖��O���擾�A�ݒ肷��B
					//���O�Ɂu_�v�͂���Ȃ����߁A+ 1�ŕ����B
					animDataBase.animName = animData[1].substr(animData[1].find("_") + 1);

					//�A�j���[�V�����ԍ���ݒ�B
					animNum++;
					animDataBase.animNum = animNum;
				}

				if (animData[kCSVTitleData] == "SPEED") {

					//�������擾�B
					animDataBase.speed = std::stof(animData[1]);
				}

				if (animData[kCSVTitleData] == "LOOP") {

					//���[�v�t���O���擾�B
					animDataBase.isLoopAnim = animData[1] == "TRUE" ? true : false;
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
			csvManager.LoadCSV(monsterAnimationEventCSVFilePath);

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
						animEvent.eventMaterial = *animEventDataItr;

						//�擪����j���B
						animEventDataList.erase(animEventDataItr);
					}
				}
			}
		}
	}
}