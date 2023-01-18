#include "YonemaEnginePreCompile.h"
#include "AIDecorator.h"
#include "MonsterAIBlackboard.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr char kDelimiter = '!';	//��؂蕶��
			}

			void CAIDecorator::Init(bool* flag) {

				//�t���O���擾�B
				m_falgRef = flag;
			}

			void CAIDecorator::Release() {

				delete this;
			}

			CAIDecorator* CAIDecoratorBuilder::CreateDecorator(const std::string& flagStr, SMonsterAIBlackboard* blackboard) {

				//�f�R���[�^�[�𐶐��B
				CAIDecorator* decorator = new CAIDecorator;

				//��������擾�B
				std::string flagStrLocal = flagStr;

				//�擪��������؂蕶���ɂȂ��Ă�����B
				if (flagStrLocal[0] == kDelimiter) {

					//�t�̕]��������悤�ݒ�B
					decorator->Reverse();
					flagStrLocal.erase(flagStrLocal.begin());
				}

				//�t���O��ݒ�B
				if (flagStrLocal == "IsFindingTarget") {

					decorator->Init(&blackboard->m_isfindingTarget);
				}
				else {
#ifdef _DEBUG
					//������Ȃ������B
					std::string errorMsg = "CAIDecorator : �w��̃t���O��������܂���ł����B : ";
					errorMsg += flagStrLocal;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif // _DEBUG
				}

				

				return decorator;
			}
		}
	}
}