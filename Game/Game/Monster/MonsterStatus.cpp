#include "YonemaEnginePreCompile.h"
#include "MonsterStatus.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsMonster {

		void CMonsterStatus::Init(const std::string& monsterName) {

			//�X�e�[�^�X��񂪓�����CSV�t�@�C���̃p�X��ݒ�B
			std::string monsterStatusCSVFilePath = "Assets/CSV/Monsters/";
			monsterStatusCSVFilePath += monsterName + "/";
			monsterStatusCSVFilePath += monsterName + "_Status.csv";

			//CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(nsUtils::GetWideStringFromString(monsterStatusCSVFilePath).c_str());

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

						//�ő�HP��HP���擾�B
						m_maxHP = std::stof(value);
						m_HP = std::stof(value);
					}
					else if (title == "ATK") {

						//�����U���͂��擾�B
						m_attack = std::stof(value);
					}
					else if (title == "INT") {

						//���@�U���͂��擾�B
						m_intelligence = std::stof(value);
					}
					else if (title == "DEF") {

						//�����h��͂��擾�B
						m_defence = std::stof(value);
					}
					else if (title == "MND") {

						//���@�h��͂��擾�B
						m_mind = std::stof(value);
					}
					else if (title == "WINCE") {

						//�Ђ�ݒl���擾�B
						m_winceValue = 0.0f;
						m_winceDelimiter = std::stof(value);
					}
				}
			}
		}

		void CMonsterStatus::HealHP(float value) {

			//HP���㏸������B
			m_HP += value;

			//�ő�HP�𒴂��Ă���Ȃ�B
			if (m_HP > m_maxHP) {

				//�ő�HP�Ɠ����ɐݒ肷��B
				m_HP = m_maxHP;
			}
		}

		void CMonsterStatus::DamageHP(float value) {

			//HP������������B
			m_HP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}
	}
}