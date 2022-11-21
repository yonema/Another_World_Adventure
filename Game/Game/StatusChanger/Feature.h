#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		//機能クラス
		class CFeature : nsUtils::SNoncopyable
		{
		public:
			virtual void Create() = 0;
		};
	}
}

