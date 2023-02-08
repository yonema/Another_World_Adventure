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
				//情報を初期化。
				m_buffOrDebuff = GetBuffOrDebuff(buffOrDebuff);
				m_statusRef = GetStatusRef(statusRef);
				m_value = value;
				m_durationTime = durationTime;
			}

			void CBuffDebuff::Create()
			{
				//ターゲットにバフデバフ情報を設定。
				m_target->GetFeatureManager()->AddStatusChanger(this);
			}

			EnBuffOrDebuff CBuffDebuff::GetBuffOrDebuff(const std::string& buffOrDebuff)const {

				//バフかデバフか調べる。
				if (buffOrDebuff == "Buff") {

					return EnBuffOrDebuff::enBuff;
				}
				else if (buffOrDebuff == "Debuff") {

					return EnBuffOrDebuff::enDebuff;
				}
				else {

					//エラー出力。
					std::string errorMsg = "CBuffDebuff : バフかデバフかの設定が不適切です。";
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

					//エラー出力。
					std::string errorMsg = "CBuffDebuff : ステータスタイプの設定が不適切です。 : ";
					errorMsg += statusRef;
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}
			}
		}
	}
}