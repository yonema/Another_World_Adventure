#pragma once

namespace nsAWA {

	//���ʂ̃X�e�[�^�X�N���X
	class CStatus : nsUtils::SNoncopyable
	{
	public:
		virtual float GetHP()const = 0;
		virtual float GetMaxHP()const = 0;
		virtual float GetMP()const = 0;
		virtual float GetMaxMP()const = 0;
		virtual float GetSP()const = 0;
		virtual float GetMaxSP()const = 0;
	};
}

