#pragma once

namespace nsAWA {

	namespace {

		constexpr float kWeak = 1.6f;	//��_
		constexpr float kNormal = 1.0f;	//�ʏ�
		constexpr float kRegist = 0.6f;	//��R
	}

	//����
	enum class EnAttribute {

		enFire,			//�Α���
		enWater,		//������
		enLightning,	//������

		enNone,			//������

		enNum			//�����̐�
	};

	//�����N���X
	class CAttribute : nsUtils::SNoncopyable
	{
	public:
		float CalcAttributeCompatibility(const EnAttribute& attribute_1, const EnAttribute& attribute_2) {

			//�����\�̒l�����^�[���B
			return m_attributeCompatibility[static_cast<int>(attribute_1)][static_cast<int>(attribute_2)];
		}
	private:
		//���������\
		float m_attributeCompatibility[static_cast<int>(EnAttribute::enNum)][static_cast<int>(EnAttribute::enNum)] =
		{
			{kNormal,kRegist,kWeak},
			{kWeak,kNormal,kRegist},
			{kRegist,kWeak,kNormal},
			{kNormal,kNormal,kNormal},
		};
	};
}