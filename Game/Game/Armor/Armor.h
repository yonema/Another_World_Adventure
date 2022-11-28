#pragma once

namespace nsAWA {

	namespace nsArmor {

		//防具情報
		struct SArmorInfo {

			const char* name = nullptr;		//名前
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

			void Create(const SArmorInfo& armorInfo, const char* modelFilePath);

			void CreateModel(const char* modelFilePath);
		public:
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

			CModelRenderer* m_modelRenderer = nullptr;		//モデル
			SArmorInfo m_sInfo;								//情報
		};

		//防具生成クラス
		class CArmorBuilder : nsUtils::SNoncopyable {

		public:
			CArmor* Create(const SArmorInfo& armorInfo, const char* modelFilePath);
		};
	}
}


