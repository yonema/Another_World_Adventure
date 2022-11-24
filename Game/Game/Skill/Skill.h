#pragma once

namespace nsAWA {

	//エイリアス宣言
	namespace nsFeature {

		class CFeature;
	}

	namespace nsSkill {

		//スキルクラス
		class CSkill : nsUtils::SNoncopyable
		{
		public:
			virtual void AddFeature(nsFeature::CFeature* feature) = 0;

		protected:
			void Create(nsFeature::CFeature* feature);
		protected:
			const char* m_name = nullptr;					//名前
			std::list<nsFeature::CFeature*> m_featureList;	//効果のリスト
		};
	}
}

