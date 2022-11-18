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
		private:
			
			CModelRenderer* m_modelRenderer = nullptr;		//モデル
			SWeaponInfo m_info;								//情報
		};

		//武器生成クラス
		class CWeaponBuilder : nsUtils::SNoncopyable {

		public:
			CWeapon* Create(const SWeaponInfo& weaponInfo, const char* modelFilePath);
		};
	}
}

