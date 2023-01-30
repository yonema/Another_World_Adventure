#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		//Œø‰Ê¶¬ƒNƒ‰ƒX
		class CFeatureBuilder : nsUtils::SNoncopyable
		{
		public:
			void CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureList);
		};
	}
}