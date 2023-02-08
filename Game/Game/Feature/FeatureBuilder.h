#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		class CFeature;
	}

	namespace nsFeature {

		//効果生成クラス
		class CFeatureBuilder : nsUtils::SNoncopyable
		{
		public:
			void CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureListStr);

			void CreateFeature(
				IGameActor* creator,
				IGameActor* target,
				std::list<std::vector<std::string>> featureListStr,
				std::list<nsFeature::CFeature**>& featureList
				);

		private:
			void Create(
				IGameActor* creator, 
				IGameActor* target,
				std::list<std::vector<std::string>> featureListStr,
				std::list<nsFeature::CFeature**>& featureList
				);

		};
	}
}