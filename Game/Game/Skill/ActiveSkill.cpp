#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"

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
	}
}