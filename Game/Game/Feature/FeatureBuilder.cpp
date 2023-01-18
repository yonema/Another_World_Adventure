#include "YonemaEnginePreCompile.h"
#include "FeatureBuilder.h"
#include "Feature.h"
#include "HealFeature.h"
#include "ApplyDamageFeature.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureBuilder::CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureList) {

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
				else if (featureStr[0] == "Damage") {
					//[1]Normal or Const
					

					//���ʂ��������B
					feature = new nsFeature::CApplyDamageFeature;

					//�ʏ�_���[�W
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
					//�Œ�_���[�W
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

						nsGameWindow::MessageBoxError(L"�_���[�W�^�C�v�̐ݒ肪�s�K�؂ł��B");
					}
				}

				//�^�[�Q�b�g��ݒ�B
				feature->SetTarget(target);

				//���ʂ𐶐��B
				feature->Create();
			}
		}
	}
}