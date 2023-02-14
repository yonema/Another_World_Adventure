#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"
#include "../CSV/CSVManager.h"
#include "PlayerWeaponManager.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/PassiveSkill.h"
#include "../Feature/FeatureManager.h"
#include "../Feature/Feature.h"
#include "../Feature/BuffDebuff.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr float kPlayerWinceDelimiter = 30.0f;	//プレイヤーのひるみ値の区切り（％）
			constexpr float kPerMax = 100.0f;			//最大％
			constexpr float kSPValue = 100.0f;			//SP量
			constexpr float kGGValue = 100.0f;			//ガードゲージ量
			constexpr float kStatusBaseInitValue = 0.0f;	//ステータス反映のための初期値
			constexpr float kStatusBaseMul = 1.0f;	//ステータス反映の初期倍率
		}

		void CPlayerStatus::Init(const nsWeapon::CWeapon* const & playerWeapon,
			const nsArmor::CArmor* const& playerArmor,
			nsSkill::CPassiveSkillManager* passiveSkillManager,
			nsFeature::CFeatureManager* featureManager
		) {

			//情報を取得。
			m_weapon = &playerWeapon;
			m_armor = &playerArmor;
			m_passiveSkillManager = passiveSkillManager;
			m_featureManager = featureManager;

			//ステータス反映のためのリストを初期化。
			ResetStatusList();	
		}

		void CPlayerStatus::Update() {

			std::list<nsFeature::CFeature*> featureList;

			//ステータス変化のリストを順に参照。
			for (const auto& feature : m_featureManager->GetStatusChanger()) {

				//効果のクラス名を取得。
				const type_info& id = typeid(*feature);

				//バフデバフなら。
				if (typeid(nsFeature::nsStatusChanger::CBuffDebuff) == id) {

					//効果のリストを順に取得。
					featureList.emplace_back(feature);
				}
			}

			//ステータス反映のためのデータを初期化。
			ResetStatusList();

			//バフデバフ量を計算して仮反映。
			//ステータスデータを順に参照。
			for (int statusRef = 0; statusRef < static_cast<int>(nsFeature::EnStatusRef::enNum); statusRef++) {

				//バフデバフリストから値を受け取る。
				for (const auto& feature : featureList) {

					auto featureRef = dynamic_cast<nsFeature::nsStatusChanger::CBuffDebuff*>(feature);

					//まず加算。
					m_statusBaseList[statusRef] += featureRef->Apply(static_cast<nsFeature::EnStatusRef>(statusRef));
				}
			}

			//各ステータスを本反映。
			m_attack = (*m_weapon)->GetAttack() * (kStatusBaseMul + m_statusBaseList[static_cast<int>(nsFeature::EnStatusRef::enAttack)]);
			m_intelligence = (*m_weapon)->GetIntelligence() * (kStatusBaseMul + m_statusBaseList[static_cast<int>(nsFeature::EnStatusRef::enInteligence)]);
			m_defence = (*m_armor)->GetDeffence() * (kStatusBaseMul + m_statusBaseList[static_cast<int>(nsFeature::EnStatusRef::enDeffence)]);
			m_mind = (*m_armor)->GetMind() * (kStatusBaseMul + m_statusBaseList[static_cast<int>(nsFeature::EnStatusRef::enMind)]);
		}

		void CPlayerStatus::LoadStatus(const std::vector<std::string>& statusDataStr) {

			//ステータスをロード。
			m_playerName = statusDataStr[0];
			m_level = std::stoi(statusDataStr[1]);
			m_exp = std::stoi(statusDataStr[2]);
			m_HP = std::stof(statusDataStr[3]);
			m_maxHP = std::stof(statusDataStr[4]);
			m_MP = std::stof(statusDataStr[5]);
			m_maxMP = std::stof(statusDataStr[6]);
			m_SP = kSPValue;
			m_maxSP = kSPValue;
			m_guardGaugeValue = kGGValue;
			m_maxGuardGaugeValue = kGGValue;
			m_winceValue = 0.0f;

			//プレイヤーのひるみ値の区切りを設定。
			m_winceDelimiter = m_maxHP * kPlayerWinceDelimiter / kPerMax;
		}

		void CPlayerStatus::ResetStatusList() {

			//ステータス反映のためのデータを初期化。
			for (auto& statusBase : m_statusBaseList) {

				statusBase = kStatusBaseInitValue;
			}
		}

		void CPlayerStatus::HealHP(float value) {

			//HPを上昇させる。
			m_HP += value;

			//最大HPを超えているなら。
			if (m_HP > m_maxHP) {

				//最大HPと同じに設定する。
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(float value) {

			//HPを減少させる。
			m_HP -= value;

			//0未満になったら0に設定する。
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}

		void CPlayerStatus::HealMP(float value) {

			//MPを上昇させる。
			m_MP += value;

			//最大MPを超えているなら。
			if (m_MP > m_maxMP) {

				//最大MPと同じに設定する。
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(float value) {

			//MPを減少させる。
			m_MP -= value;

			//0未満になったら0に設定する。
			if (m_MP < 0.0f) {

				m_MP = 0.0f;
			}
		}

		void CPlayerStatus::HealSP(float value) {

			//SPを上昇させる。
			m_SP += value;

			//最大SPを超えているなら。
			if (m_SP > m_maxSP) {

				//最大SPと同じに設定する。
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(float value) {

			//SPを減少させる。
			m_SP -= value;

			//0未満になったら0に設定する。
			if (m_SP < 0.0f) {

				m_SP = 0.0f;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(float value) {

			//ガードゲージの値を上昇させる。
			m_guardGaugeValue += value;

			//ガードゲージの最大値を超えているなら。
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//ガードゲージの最大値と同じに設定する。
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(float value) {

			//ガードゲージの値を減少させる。
			m_guardGaugeValue -= value;

			//0未満になったら0に設定する。
			if (m_guardGaugeValue < 0.0f) {

				m_guardGaugeValue = 0.0f;
			}
		}
	}
}