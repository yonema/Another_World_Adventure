#include "YonemaEnginePreCompile.h"
#include "FeatureBuilder.h"
#include "Feature.h"
#include "HealFeature.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureBuilder::CreateFeature(IGameActor* target, std::list<std::vector<std::string>> featureList) {

			//���ʂ̃��X�g�����ɎQ�ƁB
			for (const auto& featureStr : featureList) {

				//���ʂ̐��`�𐶐��B
				nsFeature::CFeature* feature = nullptr;

				//[0]...FeatureType

				//�񕜁B
				if (featureStr[0] == "Heal") {
					//[1]Type
					//[2]How
					//[3]Value

					//�����������B
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

					//���ʂ��������B
					feature = new nsFeature::CHealFeature;
					dynamic_cast<nsFeature::CHealFeature*>(feature)->Init(
						healTarget,
						howHeal,
						healValue
					);
				}

				//�^�[�Q�b�g��ݒ�B
				feature->SetTarget(target);

				//���ʂ𐶐��B
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