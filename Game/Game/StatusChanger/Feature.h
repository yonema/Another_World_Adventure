#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		//�@�\�N���X
		class CFeature : nsUtils::SNoncopyable
		{
		public:
			virtual void Create() = 0;
		};
	}
}

