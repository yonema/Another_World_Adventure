#include "YonemaEnginePreCompile.h"
#include "FeatureBuilder.h"
#include "Feature.h"
#include "HealFeature.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureBuilder::CreateFeature(IGameActor* target, std::list<std::vector<std::string>> featureList) {

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

				//ターゲットを設定。
				feature->SetTarget(target);

				//効果を生成。
				feature->Create();
				//if (featureStr[0] == "Dagame") {
				//	//[1]Type
				//	//[2]How
				//	//[3]Value
				//
				//}
			}
		}
	}
}