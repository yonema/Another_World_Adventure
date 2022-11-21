#pragma once
#include "StatusChanger.h"

namespace nsAWA {

	//�_���[�W��^����@�\
	class CApplyDamageFeature : public CFeature
	{
	public:
		void Init(
			int level,
			int power,
			float attack,
			float deffence,
			IGameActor* target,
			bool canGuard
		);

		void Create()override final;
	private:
		float m_level = 0;					//���x��
		float m_power = 0;					//�З�
		float m_attack = 0.0f;				//�U����
		float m_deffence = 0.0f;			//�h���
		IGameActor* m_target = nullptr;		//�^�[�Q�b�g
		bool m_canGuard = true;				//�K�[�h�\�H
	};
}


