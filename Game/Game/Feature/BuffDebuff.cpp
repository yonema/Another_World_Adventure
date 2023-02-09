#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "../Feature/FeatureManager.h"
#include "BuffDebuff.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			void CBuffDebuff::Init(const std::string& buffOrDebuff,
				const std::string& statusRef,
				float value,
				float durationTime
			) {
				//�����������B
				m_buffOrDebuff = GetBuffOrDebuff(buffOrDebuff);
				m_statusRef = GetStatusRef(statusRef);
				m_value = value;
				m_durationTime = durationTime;
			}

			void CBuffDebuff::Create()
			{
				//�^�[�Q�b�g�Ƀo�t�f�o�t����ݒ�B
				m_target->GetFeatureManager()->AddStatusChanger(this);
			}

			EnBuffOrDebuff CBuffDebuff::GetBuffOrDebuff(const std::string& buffOrDebuff)const {

				//�o�t���f�o�t�����ׂ�B
				if (buffOrDebuff == "Buff") {

					return EnBuffOrDebuff::enBuff;
				}
				else if (buffOrDebuff == "Debuff") {

					return EnBuffOrDebuff::enDebuff;
				}
				else {

					//�G���[�o�́B
					std::string errorMsg = "CBuffDebuff : �o�t���f�o�t���̐ݒ肪�s�K�؂ł��B";
					errorMsg += buffOrDebuff;
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}
			}

			EnStatusRef CBuffDebuff::GetStatusRef(const std::string& statusRef)const {

				if (statusRef == "ATK") {

					return EnStatusRef::enAttack;
				}
				else if (statusRef == "INT") {

					return EnStatusRef::enInteligence;
				}
				else if (statusRef == "DEF") {

					return EnStatusRef::enDeffence;
				}
				else if (statusRef == "MND") {

					return EnStatusRef::enMind;
				}
				else {

					//�G���[�o�́B
					std::string errorMsg = "CBuffDebuff : �X�e�[�^�X�^�C�v�̐ݒ肪�s�K�؂ł��B : ";
					errorMsg += statusRef;
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}
			}
		}
	}
}