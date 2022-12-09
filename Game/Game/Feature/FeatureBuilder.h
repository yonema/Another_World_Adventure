#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		//���ʐ����N���X
		class CFeatureBuilder : nsUtils::SNoncopyable
		{
		public:
			void CreateFeature(IGameActor* target, std::list<std::vector<std::string>> featureList);
		};
	}
}