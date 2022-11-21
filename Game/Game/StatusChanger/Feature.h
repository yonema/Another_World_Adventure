#pragma once

namespace nsAWA {

	//機能クラス
	class CFeature : nsUtils::SNoncopyable
	{
	public:
		virtual void Create() = 0;
	};
}

