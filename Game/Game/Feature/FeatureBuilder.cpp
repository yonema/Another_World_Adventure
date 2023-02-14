#include "YonemaEnginePreCompile.h"
#include "FeatureBuilder.h"
#include "Feature.h"
#include "HealFeature.h"
#include "ApplyDamageFeature.h"
#include "AbnormalStatus/Poison.h"
#include "AbnormalStatus/Paralysis.h"
#include "BuffDebuff.h"
#include "../Attribute.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeatureBuilder::CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureListStr) {

			std::list<nsFeature::CFeature*> featureListEmpty;
			//効果を生成。
			Create(creator, target, featureListStr, featureListEmpty);
		}

		void CFeatureBuilder::CreateFeature(
			IGameActor* creator,
			IGameActor* target,
			std::list<std::vector<std::string>> featureListStr,
			std::list<nsFeature::CFeature*>& featureList
		) {

			//効果を生成。
			Create(creator, target, featureListStr, featureList);
		}

		void CFeatureBuilder::Create(
			IGameActor* creator,
			IGameActor* target,
			std::list<std::vector<std::string>> featureListStr,
			std::list<nsFeature::CFeature*>& featureList
			) {

			//効果のリストを順に参照。
			for (const auto& featureStr : featureListStr) {

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
						//[3]Attribute
						//[4]power
						//[5]canGuard

						//属性を設定。
						EnAttribute attribute = EnAttribute::enNone;
						if (featureStr[3] == "Fire") {

							attribute = EnAttribute::enFire;
						}
						else if (featureStr[3] == "Water") {

							attribute = EnAttribute::enWater;
						}
						else if (featureStr[3] == "Lightning") {

							attribute = EnAttribute::enLightning;
						}
						else if (featureStr[3] == "None") {

							attribute = EnAttribute::enNone;
						}
						else {

							//エラー出力。
							nsGameWindow::MessageBoxWarning(L"CFeatureBuilder : 属性が指定されていません。");
						}

						dynamic_cast<nsFeature::CApplyDamageFeature*>(feature)->Init(
							creator,
							target,
							attribute,
							std::stof(featureStr[4]),
							featureStr[2],
							featureStr[5] == "TRUE" ? true : false
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
					feature = new nsFeature::nsStatusChanger::CPoison;

					//毒レベルを取得。
					int poisonLevel = std::stoi(featureStr[1]);

					//毒機能を生成。
					dynamic_cast<nsFeature::nsStatusChanger::CAbnormalStatus*>(feature)->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
						poisonLevel
					);
				}
				//麻痺。
				else if (featureType == "Paralysis") {
					//[1]ParalysisLevel

					//効果を初期化。
					feature = new nsFeature::nsStatusChanger::CParalysis;

					//麻痺レベルを取得。
					int paralysisLevel = std::stoi(featureStr[1]);

					//麻痺機能を生成。
					dynamic_cast<nsFeature::nsStatusChanger::CAbnormalStatus*>(feature)->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enParalysis,
						paralysisLevel
					);
				}
				//バフデバフ。
				else if (featureType == "BuffDebuff") {
					//[1]BuffOrDebuff
					//[2]StatusRef
					//[3]Value
					//[4]DurationTime

					//効果を初期化。
					feature = new nsFeature::nsStatusChanger::CBuffDebuff;

					//バフかデバフか取得。
					std::string buffOrDebuff = featureStr[1];

					//参照ステータスを取得。
					std::string StatusRef = featureStr[2];

					//値を取得。
					float value = std::stof(featureStr[3]);

					//持続時間を取得。
					float DurationTime = std::stof(featureStr[4]);

					//バフデバフ機能を生成。
					dynamic_cast<nsFeature::nsStatusChanger::CBuffDebuff*>(feature)->Init(
						buffOrDebuff,
						StatusRef,
						value,
						DurationTime
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

				//リストに追加。
				featureList.emplace_back(feature);
			}
		}
	}
}