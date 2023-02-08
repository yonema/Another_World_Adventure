#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsFeature {

		class CFeature;
	}

	namespace nsSkill {

		//スキルクラス
		class CSkill : nsUtils::SNoncopyable
		{
		public:

			void SetName(const std::string& name) {

				//名前を設定。
				m_name = name;
			}

			const std::string& GetName()const {

				//名前を取得。
				return m_name;
			}

		protected:
			void Create(nsFeature::CFeature* feature);

		protected:
			std::string m_name = "NoName";					//名前
		};
	}
}

