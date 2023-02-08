#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//パッシブスキル
		class CPassiveSkill : public CSkill
		{
		public:
			void SetFeatureListStr(std::list<std::vector<std::string>> featureListStr) {

				//効果のリストの文字列を設定。
				m_featureListStr = featureListStr;
			}

			const std::list<std::vector<std::string>>& GetFeatureListStr()const {

				//効果のリストの文字列を取得。
				return m_featureListStr;
			}

			void SetFeatureList(const std::list<nsFeature::CFeature*>& featureList) {

				//効果のリストを設定。
				m_featureList = featureList;
			}

			std::list<nsFeature::CFeature*>& GetFeatureList() {

				//効果のリストを取得。
				return m_featureList;
			}

			void Update();

		private:
			std::list<std::vector<std::string>> m_featureListStr;//効果のリストの文字列
			std::list<nsFeature::CFeature*> m_featureList;		//効果のリスト
		};
	}
}

