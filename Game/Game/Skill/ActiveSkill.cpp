#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"
#include "../Player/Player.h"

namespace nsAWA {

	namespace nsSkill {

		int CActiveSkill::m_kActiveSkillNumMax = 6;

		const CActiveSkill::SActiveSkillAnimData& CActiveSkill::GetActiveSkillAnimData(const std::string& index)const {

			//アクティブスキルのアニメーションデータを順に参照。
			for (const auto& animData : m_activeSkillAnimDataList) {

				//インデックスが一致したら。
				if (animData.index == index) {

					//そのアニメーションデータをリターン。
					return animData;
				}
			}
			
#ifdef _DEBUG
			//エラー出力。
			nsGameWindow::MessageBoxError(L"CActiveSkill : スキルのアニメーションデータが見つかりませんでした。");
			std::abort();
#endif // _DEBUG
		}

		void CActiveSkill::Execute() {

			if (m_effectName != "NoName") {

				//プレイヤーに武器管理クラスを取得。
				auto playerWeaponManager = dynamic_cast<nsPlayer::CPlayer*>(FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player))->GetWeaponManager();
				
				//エフェクトを生成。
				playerWeaponManager->CreateEffect(m_effectName);
			}
		}
	}
}