#include "YonemaEnginePreCompile.h"
#include "FeatureBuilder.h"
#include "Feature.h"
#include "HealFeature.h"
#include "ApplyDamageFeature.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureBuilder::CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureList) {

			//効果のリストを順に参照。
			for (const auto& featureStr : featureList) {

				//効果の雛形を生成。
				nsFeature::CFeature* feature = nullptr;

				//[0]...FeatureType

				//回復。
				if (featureStr[0] == "Heal") {
					//[1]Type
					//[2]How
					//[3]Value

					//情報を初期化。
					nsFeature::EnHealTarget healTarget = nsFeature::EnHealTarget::enNone;
					{
						if (featureStr[1] == "HP") {
							healTarget = nsFeature::EnHealTarget::enHP;
						}
						else if (featureStr[1] == "MP") {
							healTarget = nsFeature::EnHealTarget::enMP;
						}
						else if (featureStr[1] == "SP") {
							healTarget = nsFeature::EnHealTarget::enSP;
						}
					}
					nsFeature::EnHowHeal howHeal = nsFeature::EnHowHeal::enNone;
					{
						if (featureStr[2] == "Const") {
							howHeal = nsFeature::EnHowHeal::enConst;
						}
						else if (featureStr[2] == "Ratio") {
							howHeal = nsFeature::EnHowHeal::enRatio;
						}
					}
					float healValue = std::stof(featureStr[3]);

					//効果を初期化。
					feature = new nsFeature::CHealFeature;
					dynamic_cast<nsFeature::CHealFeature*>(feature)->Init(
						healTarget,
						howHeal,
						healValue
					);
				}
				else if (featureStr[0] == "Damage") {
					//[1]Normal or Const
					

					//効果を初期化。
					feature = new nsFeature::CApplyDamageFeature;

					//通常ダメージ
					if (featureStr[1] == "Normal") {

						//[2]Physical or Magic
						//[3]power
						//[4]canGuard

						dynamic_cast<nsFeature::CApplyDamageFeature*>(feature)->Init(
							creator,
							target,
							std::stof(featureStr[3]),
							featureStr[2],
							featureStr[4] == "TRUE" ? true : false
						);
					}
					//固定ダメージ
					else if (featureStr[1] == "Const") {

						//[2]Const or Ratio
						//[3]damage
						//[4]canGuard

						dynamic_cast<nsFeature::CApplyDamageFeature*>(feature)->Init(
							featureStr[2],
							target,
							std::stof(featureStr[3]),
							featureStr[4] == "TRUE" ? true : false
						);
					}
					else {

						nsGameWindow::MessageBoxError(L"ダメージタイプの設定が不適切です。");
					}
				}

				//ターゲットを設定。
				feature->SetTarget(target);

				//効果を生成。
				feature->Create();
			}
		}
	}
}