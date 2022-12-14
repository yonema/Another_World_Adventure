#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		//効果生成クラス
		class CFeatureBuilder : nsUtils::SNoncopyable
		{
		public:
			void CreateFeature(IGameActor* creator, IGameActor* target, std::list<std::vector<std::string>> featureList);
		};
	}
}