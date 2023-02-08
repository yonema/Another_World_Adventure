#pragma once
#include "MagicBase.h"

namespace nsAWA {

	namespace nsMagic {

		//�^���������ł������@�i�P�j
		class CMagicBallOne : public CMagicBase
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		private:
			void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

		private:
			CEffectPlayer* m_mainEffect = nullptr;	//���C���̃G�t�F�N�g
			CPhysicsTriggerObject m_trigger;	//�����蔻��
			
			
			float m_durationTime = 0.0f;		//��������

			
		};
	}
}