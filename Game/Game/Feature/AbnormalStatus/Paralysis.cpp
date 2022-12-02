#include "YonemaEnginePreCompile.h"
#include "Paralysis.h"
#include <random>

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			namespace {

				constexpr int kCanAttackPer = 70;		//�A�N�e�B�u�X�L�����g�p�ł���m���i���j
				constexpr int kPerMax = 100;			//�ő�m���i���j
			}

			void CParalysis::Init() {

				//�U���ł��邩�ǂ����̕ϐ����������B
				m_canUseActiveSkill = true;
			}

			void CParalysis::Execute(float deltaTime) {

				//�A�N�e�B�u�X�L�����g�p�ł��邩�𒊑I�B
				{
					//�Q��̗���������𐶐��B�����_���f�o�C�X����seed�l�����肵�A�����ȗ����������p���ė����𐶐�����B
					std::random_device rd;
					std::mt19937_64 mt(rd());

					//�������l�𒊑I�B
					int canAttackPer = mt() % kPerMax;

					//���I���ꂽ�l���A�N�e�B�u�X�L�����g�p�ł���m���i���j��菬�����Ȃ�B
					if (canAttackPer < kCanAttackPer) {

						//�U���\�B
						m_canUseActiveSkill = true;
					}
					//�A�N�e�B�u�X�L�����g�p�ł���m���i���j�ȏ�Ȃ�B
					else {

						//�A�N�e�B�u�X�L�����g�p�s�B
						m_canUseActiveSkill = false;
					}
				}
			}
		}
	}
}