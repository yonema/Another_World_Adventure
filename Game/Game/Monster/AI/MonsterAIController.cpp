#include "YonemaEnginePreCompile.h"
#include "../Utils/StringManipulation.h"
#include "../Monster.h"
#include "MonsterAIController.h"
#include "../../CSV/CSVManager.h"
#include "AITask/AITaskBuilder.h"
#include "AITask/AITaskWait.h"
#include "AISequence.h"
#include "AISelector.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CMonsterAIController::Init(CMonster* owner) {

				//�Q�[���A�N�^�[��ݒ�B
				m_owner = owner;

				//���O���擾�B
				std::string monsterName = owner->GetName();

				//AI��񂪓�����CSV�̃t�@�C���p�X��ݒ�B
				std::string monsterStatusCSVFilePath = "Assets/CSV/Monsters/";
				monsterStatusCSVFilePath += monsterName + "/";
				monsterStatusCSVFilePath += monsterName + "_AI.csv";

				//CSV�����[�h�B
				nsCSV::CCsvManager csvManager;
				csvManager.LoadCSV(nsUtils::GetWideStringFromString(monsterStatusCSVFilePath).c_str());

				//CSV�f�[�^���擾�B
				AIPartsDataStr strData = csvManager.GetCsvData();

				//�r�w�C�r�A�c���[���\�z�B
				m_rootNode = CreateAIPart(strData);
			}

			void CMonsterAIController::Release() {

				if (m_rootNode != nullptr) {

					//�m�[�h��j���B
					m_rootNode->Release();
				}
			}

			CAIPart* CMonsterAIController::CreateAIPart(AIPartsDataStr& AIPartsData) {

				//�擪�̃C�e���[�^���擾�B
				auto itr = AIPartsData.begin();

				//��ނ��擾�B
				std::string type = *(*itr).begin();
				(*itr).erase((*itr).begin());

				//���O���擾�B
				std::string name = *(*itr).begin();
				(*itr).erase((*itr).begin());

				//�q�m�[�h�̐����擾�B
				int cNodeNum = std::stoi(*(*itr).begin());
				(*itr).erase((*itr).begin());

				//AI���i�̐��`�𐶐��B
				CAIPart* aiPart = nullptr;

				//AI���i���\�z�B
				{
					if (type == "Sequence") {

						//�V�[�P���X�𐶐��B
						aiPart = new CAISequence;

						//�f�R���[�^�[��ǉ��B
						CAIDecoratorBuilder m_decoratorBuilder;

						if ((*itr).size() > 0) {

							for (const auto& decoratorStr : (*itr)) {

								aiPart->AddDecorator(m_decoratorBuilder.CreateDecorator(decoratorStr, &m_blackboard));
							}
						}
					}
					else if (type == "Selector") {

						//�Z���N�^�[�𐶐��B
						aiPart = new CAISelector;

						//�f�R���[�^�[��ǉ��B
						CAIDecoratorBuilder m_decoratorBuilder;

						if ((*itr).size() > 0) {

							for (const auto& decoratorStr : (*itr)) {

								aiPart->AddDecorator(m_decoratorBuilder.CreateDecorator(decoratorStr, &m_blackboard));
							}
						}
					}
					else if (type == "Task") {

						//�^�X�N�𐶐��B
						CAITaskBuilder AITaskBuilder;
						aiPart = AITaskBuilder.GetAITask(name);
					}
					else {

						//������Ȃ������B
						std::string errorMsg = "�w���AI���i��������܂���ł����B : ";
						errorMsg += type;

						//�x���E�B���h�E���o�́B
						nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					}

					//���O��ݒ�B
					aiPart->SetName(name);

					//����ݒ�B
					aiPart->SetPartInfo(*itr);

					//AI�R���g���[���[��ݒ�B
					aiPart->SetAIController(this);
				}

				//�擪�v�f���폜�B
				AIPartsData.erase(itr);

				//�q�m�[�h�̐�����AI���i�𐶐��B
				for (int carentNodeNum = 0; carentNodeNum < cNodeNum; carentNodeNum++) {

					//����AI���i�̎q�ɐ�������AI���i��ǉ��B
					aiPart->AddAIPart(CreateAIPart(AIPartsData));
				}

				//���g�����^�[���B
				return aiPart;
			}

			void CMonsterAIController::Update(float deltaTime) {

				//�N�[���^�C�����Ȃ�B
				if (m_isCoolTime) {

					//�������^�[���B
					return;
				}

				//�f���^�^�C�����X�V�B
				m_deltaTimeRef = deltaTime;

				//��]�����X�V�B
				UpdateForwardDirection();

				//�ҋ@�^�X�N�����s���Ȃ�B
				if (m_waitNode != nullptr) {

					//�ҋ@�^�X�N���������s�B
					bool isOk = m_waitNode->Execute(m_blackboard, m_waitNode->GetPartInfo());

					//�ҋ@�I��������B
					if (isOk) {

						//�������B
						m_waitNode = nullptr;
					}
				}
				else {

					//���[�g�m�[�h����r�w�C�r�A�c���[�����s�B
					m_rootNode->Execute(m_blackboard, m_rootNode->GetPartInfo());
				}
			}

			void CMonsterAIController::SetPosition(const CVector3& position) {

				//���W��ݒ�B
				m_owner->SetPosition(position);
			}

			const CVector3& CMonsterAIController::GetPosition()const {

				//���W���擾�B
				return m_owner->GetPosition();
			}

			void CMonsterAIController::SetRotation(const CQuaternion& rotation) {

				//��]��ݒ�B
				m_owner->SetRotation(rotation);
			}

			const CQuaternion& CMonsterAIController::GetRotation()const {

				//��]���擾�B
				return m_owner->GetRotation();
			}

			const CVector3& CMonsterAIController::GetForwardDirection()const {

				//�O�������擾�B
				return m_owner->GetForwardDirection();
			}

			void CMonsterAIController::UpdateForwardDirection() {

				//��]�s����v�Z�B
				auto mRot = CMatrix::Identity();
				mRot.MakeRotationFromQuaternion(m_owner->GetRotation());

				//�O�������擾�B
				CVector3 forwardDirection = m_owner->GetForwardDirection();

				//�O������ݒ�B
				forwardDirection.x = mRot.m_fMat[2][0];
				forwardDirection.y = mRot.m_fMat[2][1];
				forwardDirection.z = mRot.m_fMat[2][2];

				//���K���B
				forwardDirection.Normalize();

				//�O������ݒ�B
				m_owner->SetForwardDirection(forwardDirection);
			}

			void CMonsterAIController::SetState(const EnMonsterState& state) {

				//�X�e�[�g��ݒ�B
				m_owner->SetState(state);
			}

			const EnMonsterState& CMonsterAIController::GetState()const {

				//�X�e�[�g���擾�B
				return m_owner->GetState();
			}
		}
	}
}