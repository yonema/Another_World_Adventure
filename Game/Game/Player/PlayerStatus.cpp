#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const wchar_t* kPlayerStatusCSVFilePath = L"Assets/CSV/Player/Player_Status.csv";	//�v���C���[�X�e�[�^�X��CSV�̃t�@�C���p�X
			constexpr float kPlayerWinceDelimiter = 30.0f;	//�v���C���[�̂Ђ�ݒl�̋�؂�i���j
			constexpr float kPerMax = 100.0f;			//�ő偓
		}

		void CPlayerStatus::Init() {

			//�X�e�[�^�X���[�h�����B
			LoadStatus();

#ifdef _DEBUG

			m_attack = 2.0f;

			m_intelligence = 2.0f;

			m_defence = 2.0f;
			m_mind = 2.0f;
#endif
			
		}

		void CPlayerStatus::LoadStatus() {

			//CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kPlayerStatusCSVFilePath);

			//CSV�f�[�^�����ɎQ�ƁB
			for (const auto& lineData : csvManager.GetCsvData()) {

				//���o�������擾�B
				std::string title = lineData[0];

				//�l���擾�B
				std::string value = lineData[1];

				//�f�[�^���擾�B
				{
					if (title == "LEVEL") {

						//���x�����擾�B
						m_level = std::stoi(value);
					}
					else if (title == "HP") {

						//HP���擾�B
						m_HP = std::stof(value);
					}
					else if (title == "MAXHP") {

						//�ő�HP���擾�B
						m_maxHP = std::stof(value);
					}
					else if (title == "MP") {

						//MP���擾�B
						m_MP = std::stof(value);
					}
					else if (title == "MAXMP") {

						//�ő�MP���擾�B
						m_maxMP = std::stof(value);
					}
					else if (title == "SP") {

						//SP���擾�B
						m_SP = std::stof(value);
					}
					else if (title == "MAXSP") {

						//�ő�SP���擾�B
						m_maxSP = std::stof(value);
					}
					else if (title == "GG") {

						//�K�[�h�Q�[�W�̒l���擾�B
						m_guardGaugeValue = std::stof(value);
					}
					else if (title == "MAXGG") {

						//�K�[�h�Q�[�W�̍ő�l���擾�B
						m_maxGuardGaugeValue = std::stof(value);
					}
					else if (title == "WINCE") {

						//�Ђ�ݒl���擾�B
						m_winceValue = std::stof(value);
					}

					//�v���C���[�̂Ђ�ݒl�̋�؂��ݒ�B
					m_winceDelimiter = m_maxHP * kPlayerWinceDelimiter / kPerMax;
				}
			}
		}

		void CPlayerStatus::HealHP(float value) {

			//HP���㏸������B
			m_HP += value;

			//�ő�HP�𒴂��Ă���Ȃ�B
			if (m_HP > m_maxHP) {

				//�ő�HP�Ɠ����ɐݒ肷��B
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(float value) {

			//HP������������B
			m_HP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}

		void CPlayerStatus::HealMP(float value) {

			//MP���㏸������B
			m_MP += value;

			//�ő�MP�𒴂��Ă���Ȃ�B
			if (m_MP > m_maxMP) {

				//�ő�MP�Ɠ����ɐݒ肷��B
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(float value) {

			//MP������������B
			m_MP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_MP < 0.0f) {

				m_MP = 0.0f;
			}
		}

		void CPlayerStatus::HealSP(float value) {

			//SP���㏸������B
			m_SP += value;

			//�ő�SP�𒴂��Ă���Ȃ�B
			if (m_SP > m_maxSP) {

				//�ő�SP�Ɠ����ɐݒ肷��B
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(float value) {

			//SP������������B
			m_SP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_SP < 0.0f) {

				m_SP = 0.0f;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(float value) {

			//�K�[�h�Q�[�W�̒l���㏸������B
			m_guardGaugeValue += value;

			//�K�[�h�Q�[�W�̍ő�l�𒴂��Ă���Ȃ�B
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//�K�[�h�Q�[�W�̍ő�l�Ɠ����ɐݒ肷��B
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(float value) {

			//�K�[�h�Q�[�W�̒l������������B
			m_guardGaugeValue -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_guardGaugeValue < 0.0f) {

				m_guardGaugeValue = 0.0f;
			}
		}
	}
}