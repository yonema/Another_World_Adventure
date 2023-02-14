#pragma once

namespace nsAWA {

	namespace {

		constexpr float kWeak = 1.6f;	//弱点
		constexpr float kNormal = 1.0f;	//通常
		constexpr float kRegist = 0.6f;	//抵抗
	}

	//属性
	enum class EnAttribute {

		enFire,			//火属性
		enWater,		//水属性
		enLightning,	//雷属性

		enNone,			//無属性

		enNum			//属性の数
	};

	//属性クラス
	class CAttribute : nsUtils::SNoncopyable
	{
	public:
		float CalcAttributeCompatibility(const EnAttribute& attribute_1, const EnAttribute& attribute_2) {

			//相性表の値をリターン。
			return m_attributeCompatibility[static_cast<int>(attribute_1)][static_cast<int>(attribute_2)];
		}
	private:
		//属性相性表
		float m_attributeCompatibility[static_cast<int>(EnAttribute::enNum)][static_cast<int>(EnAttribute::enNum)] =
		{
			{kNormal,kRegist,kWeak},
			{kWeak,kNormal,kRegist},
			{kRegist,kWeak,kNormal},
			{kNormal,kNormal,kNormal},
		};
	};
}