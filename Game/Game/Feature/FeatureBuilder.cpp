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
			//���ʂ𐶐��B
			Create(creator, target, featureListStr, featureListEmpty);
		}

		void CFeatureBuilder::CreateFeature(
			IGameActor* creator,
			IGameActor* target,
			std::list<std::vector<std::string>> featureListStr,
			std::list<nsFeature::CFeature*>& featureList
		) {

			//���ʂ𐶐��B
			Create(creator, target, featureListStr, featureList);
		}

		void CFeatureBuilder::Create(
			IGameActor* creator,
			IGameActor* target,
			std::list<std::vector<std::string>> featureListStr,
			std::list<nsFeature::CFeature*>& featureList
			) {

			//���ʂ̃��X�g�����ɎQ�ƁB
			for (const auto& featureStr : featureListStr) {

				//���ʂ̐��`�𐶐��B
				nsFeature::CFeature* feature = nullptr;

				//[0]...FeatureType
				//���ʂ̎�ނ��擾�B
				std::string featureType = featureStr[0];

				//�񕜁B
				if (featureType == "Heal") {
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
				//�_���[�W�B
				else if (featureType == "Damage") {
					//[1]Normal or Const


					//���ʂ��������B
					feature = new nsFeature::CApplyDamageFeature;

					//�ʏ�_���[�W
					if (featureStr[1] == "Normal") {

						//[2]Physical or Magic
						//[3]Attribute
						//[4]power
						//[5]canGuard

						//������ݒ�B
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

							//�G���[�o�́B
							nsGameWindow::MessageBoxWarning(L"CFeatureBuilder : �������w�肳��Ă��܂���B");
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
				//�ŁB
				else if (featureType == "Poison") {
					//[1]PoisonLevel

					//���ʂ��������B
					feature = new nsFeature::nsStatusChanger::CPoison;

					//�Ń��x�����擾�B
					int poisonLevel = std::stoi(featureStr[1]);

					//�ŋ@�\�𐶐��B
					dynamic_cast<nsFeature::nsStatusChanger::CAbnormalStatus*>(feature)->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
						poisonLevel
					);
				}
				//��ჁB
				else if (featureType == "Paralysis") {
					//[1]ParalysisLevel

					//���ʂ��������B
					feature = new nsFeature::nsStatusChanger::CParalysis;

					//��Ⴣ��x�����擾�B
					int paralysisLevel = std::stoi(featureStr[1]);

					//��჋@�\�𐶐��B
					dynamic_cast<nsFeature::nsStatusChanger::CAbnormalStatus*>(feature)->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enParalysis,
						paralysisLevel
					);
				}
				//�o�t�f�o�t�B
				else if (featureType == "BuffDebuff") {
					//[1]BuffOrDebuff
					//[2]StatusRef
					//[3]Value
					//[4]DurationTime

					//���ʂ��������B
					feature = new nsFeature::nsStatusChanger::CBuffDebuff;

					//�o�t���f�o�t���擾�B
					std::string buffOrDebuff = featureStr[1];

					//�Q�ƃX�e�[�^�X���擾�B
					std::string StatusRef = featureStr[2];

					//�l���擾�B
					float value = std::stof(featureStr[3]);

					//�������Ԃ��擾�B
					float DurationTime = std::stof(featureStr[4]);

					//�o�t�f�o�t�@�\�𐶐��B
					dynamic_cast<nsFeature::nsStatusChanger::CBuffDebuff*>(feature)->Init(
						buffOrDebuff,
						StatusRef,
						value,
						DurationTime
					);
				}
				else {

					//���ʂ̎�ނ��s�K�؂Ȃ̂Ōx�����o�́B
					std::string errorMsg = "CFeatureBuilder : ���ʂ̎�ނ��s�K�؂ł��B : ";
					errorMsg += featureType;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}

				//�^�[�Q�b�g��ݒ�B
				feature->SetTarget(target);

				//���ʂ̐����҂�ݒ�B
				feature->SetCreator(creator);

				//���ʂ𐶐��B
				feature->Create();

				//���X�g�ɒǉ��B
				featureList.emplace_back(feature);
			}
		}
	}
}