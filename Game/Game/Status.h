#pragma once

namespace nsAWA {

	//共通のステータスクラス
	class CStatus : nsUtils::SNoncopyable
	{
	public:
		virtual float GetMaxHP()const = 0;
	};
}

