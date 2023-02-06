#include "YonemaEnginePreCompile.h"
#include "FeatureBuilder.h"
#include "Feature.h"
#include "HealFeature.h"
#include "ApplyDamageFeature.h"
#include "AbnormalStatus/Poison.h"
#include "AbnormalStatus/Paralysis.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureBuilder::CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureList) {

			//効果のリストを順に参照。
			for (const auto& featureStr : featureList) {

				//効果の雛形を生成。
				nsFeature::CFeature* feature = nullptr;

				//[0]...FeatureType
				//効果の種類を取得。
				std::string featureType = featureStr[0];

				//回復。
				if (featureType == "Heal") {
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
				//ダメージ。
				else if (featureType == "Damage") {
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
				//毒。
				else if (featureType == "Poison") {
					//[1]PoisonLevel

					//効果を初期化。
					feature = new nsFeature::nsStatusChanger::CAbnormalStatus;

					//毒レベルを取得。
					int poisonLevel = std::stoi(featureStr[1]);

					//毒機能を生成。
					feature = new nsFeature::nsStatusChanger::CAbnormalStatus;
					dynamic_cast<nsFeature::nsStatusChanger::CAbnormalStatus*>(feature)->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
						poisonLevel
					);
				}
				//麻痺。
				else if (featureType == "Paralysis") {
					//[1]ParalysisLevel

					//効果を初期化。
					feature = new nsFeature::nsStatusChanger::CAbnormalStatus;

					//麻痺レベルを取得。
					int paralysisLevel = std::stoi(featureStr[1]);

					//麻痺機能を生成。
					feature = new nsFeature::nsStatusChanger::CAbnormalStatus;
					dynamic_cast<nsFeature::nsStatusChanger::CAbnormalStatus*>(feature)->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enParalysis,
						paralysisLevel
					);
				}
				else {

					//効果の種類が不適切なので警告を出力。
					std::string errorMsg = "CFeatureBuilder : 効果の種類が不適切です。 : ";
					errorMsg += featureType;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}

				//ターゲットを設定。
				feature->SetTarget(target);

				//効果の生成者を設定。
				feature->SetCreator(creator);

				//効果を生成。
				feature->Create();
			}
		}
	}
}