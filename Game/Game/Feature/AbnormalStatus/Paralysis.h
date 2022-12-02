#pragma once
#include "AbnormalStatus.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			//��ჃN���X
			class CParalysis : public CAbnormalStatus
			{
			public:
				void Init()override final;

				void Execute(float deltaTime)override final;

				bool CanUseActiveSkill()const {

					//�A�N�e�B�u�X�L�����g�p�ł��邩�����^�[���B
					return m_canUseActiveSkill;
				}
			private:
				bool m_canUseActiveSkill = false;	//�A�N�e�B�u�X�L�����g�p�ł���H
			};
		}
	}
}

