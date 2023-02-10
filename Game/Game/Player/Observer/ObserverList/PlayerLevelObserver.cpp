#include "YonemaEnginePreCompile.h"
#include "PlayerLevelObserver.h"
#include "../ObservablePlayer.h"
#include "../../../CSV/CSVManager.h"
#include "../../../GameLog/GameLog.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			namespace {

				constexpr const wchar_t* kExpTableCSVFilePath = L"Assets/CSV/Player/ExpTable.csv";	//�o���l�e�[�u����CSV�̃t�@�C���p�X
			}

			void CPlayerLevelObserver::InitSub(CObservablePlayer* observablePlayer) {

				//�o���l�e�[�u����CSV�����[�h�B
				nsCSV::CCsvManager csvManager;
				csvManager.LoadCSV(kExpTableCSVFilePath);

				//�o���l�e�[�u�����쐬�B
				for (const auto& expDataStr : csvManager.GetCsvData()) {

					std::vector<int> expData;

					for (const auto& expDataStrDetail : expDataStr) {

						expData.emplace_back(std::stoi(expDataStrDetail));
					}

					//�擾�����������X�g�ɒǉ��B
					m_expTable.emplace_back(expData);
				}

				//���݂̃v���C���[�̃��x�����擾�B
				m_oldPlayerLevel = observablePlayer->GetLevel();
			}

			void CPlayerLevelObserver::Update(CObservablePlayer* observablePlayer) {

				//�o���l���擾�B
				int exp = observablePlayer->GetExp();

				//���x�����擾�B
				int level = observablePlayer->GetLevel();

				//�o���l�e�[�u�������x���̏ꏊ���珇�ɎQ�ƁB
				for (int levelNum = level; levelNum < m_expTable.size(); levelNum++) {

					//��r�o���l�܂ŃX�L�b�v�B
					if (m_expTable[levelNum][static_cast<int>(EnExpTableVectorInfo::enNeedExp)] <= exp) {

						//���x�����ꎞ�ۑ��B
						level = m_expTable[levelNum][static_cast<int>(EnExpTableVectorInfo::enLevel)];

						//���ցB
						continue;
					}

					//�O�����̃��x���̌o���l�ɓ��B���Ă���Ȃ�B
					if (level > m_oldPlayerLevel) {

						//���x���A�b�v�B
						observablePlayer->SetLevel(level);

						std::string levelUpText = "���x����";
						levelUpText += std::to_string(level);
						levelUpText += "�ɏオ����!";

						//���x���A�b�v�e�L�X�g��\���B
						nsGameLog::CGameLog::GetInstance()->AddGameLog(levelUpText);
					}

					//�I���B
					return;
				}
			}
		}
	}
}