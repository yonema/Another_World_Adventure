#pragma once
#include "MagicBase.h"

namespace nsAWA {

	namespace nsMagic {

		//�v���C���[�ɖ��@��������N���X
		class CMagicToPlayer : public CMagicBase
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		private:
			CEffectPlayer* m_effect = nullptr;	//�G�t�F�N�g
			float m_effectDurationTime = 0.0f;	//�G�t�F�N�g�̎�������
		};
	}
}