#pragma once

namespace nsAWA {

	namespace nsWeapon {

		//武器の種類
		enum class EnWeaponType {

			enSword,	//剣
			enAxe,		//斧
			enWand,		//杖

			enNum,		//武器数
			enNone		//設定なし
		};

		//武器情報
		struct SWeaponInfo {

			EnWeaponType weaponType = EnWeaponType::enNone;	//武器の種類
			const char* name = nullptr;		//名前
			float attack = 0.0f;			//物理攻撃力
			float intelligence = 0.0f;		//魔法攻撃力
			float critical = 0.0f;			//クリティカル率
		};

		//武器クラス
		class CWeapon : nsUtils::SNoncopyable
		{
			//武器生成クラスはフレンド
			friend class CWeaponBuilder;
		public:

			void Release();
		private:

			void Create(const SWeaponInfo& weaponInfo, const char* modelFilePath);

			void CreateModel(const char* modelFilePath);

		public:
			void SetAttack(float attack) {

				m_sInfo.attack = attack;
			}
			float GetAttack()const {

				return m_sInfo.attack;
			}

			void SetIntelligence(float intelligence) {

				m_sInfo.intelligence = intelligence;
			}
			float GetIntelligence()const {

				return m_sInfo.intelligence;
			}

			void SetCritical(float critical) {

				m_sInfo.critical = critical;
			}
			float GetCritical()const {

				return m_sInfo.critical;
			}

			void SetPosition(const CVector3& position) {

				//座標を設定。
				m_modelRenderer->SetPosition(position);
			}

			const CVector3& GetPosition()const {

				//座標を取得。
				return m_modelRenderer->GetPosition();
			}

			void SetRotation(const CQuaternion& rotation) {

				//回転を設定。
				m_modelRenderer->SetRotation(rotation);
			}

			const CQuaternion& GetRotation()const {

				//回転を取得。
				return m_modelRenderer->GetRotation();
			}

			void SetScale(const CVector3& scale) {

				//拡大率を設定。
				m_modelRenderer->SetScale(scale);
			}

			const CVector3& GetScale()const {

				//拡大率を取得。
				m_modelRenderer->GetScale();
			}


		private:
			
			CModelRenderer* m_modelRenderer = nullptr;		//モデル
			SWeaponInfo m_sInfo;							//情報
		};

		//武器生成クラス
		class CWeaponBuilder : nsUtils::SNoncopyable {

		public:
			CWeapon* Create(const SWeaponInfo& weaponInfo, const char* modelFilePath);
		};
	}
}

