#pragma once

namespace nsAWA {

	namespace nsArmor {

		//防具情報
		struct SArmorInfo {

			std::string name = "NoName";		//名前
			float defence = 0.0f;			//物理防御力
			float mind = 0.0f;				//魔法防御力
		};

		//防具クラス
		class CArmor : nsUtils::SNoncopyable
		{
			//防具生成クラスはフレンド
			friend class CArmorBuilder;
		public:

			void Release();
		private:

			void Create(const SArmorInfo& armorInfo);
		public:
			const std::string& GetArmorName()const {

				//防具の名前を取得。
				return m_sInfo.name;
			}

			float GetDeffence()const {

				return m_sInfo.defence;
			}
			void SetDeffence(float deffence) {

				m_sInfo.defence = deffence;
			}

			float GetMind()const {

				return m_sInfo.mind;
			}
			void SetMind(float mind) {

				m_sInfo.mind = mind;
			}
		private:
			SArmorInfo m_sInfo;								//情報
		};

		//防具生成クラス
		class CArmorBuilder : nsUtils::SNoncopyable {

		public:
			CArmor* CreateArmor(const std::string& armorName);
		};
	}
}


