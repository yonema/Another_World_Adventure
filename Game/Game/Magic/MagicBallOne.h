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

			void SetPosition(const CVector3& position)override final {

				//���W��ݒ�B
				m_position = position;
			}

			void AddPosition(const CVector3& addPosition) {

				m_position += addPosition;
			}

			void SetMoveDirection(const CVector3& moveDirection) {

				//���ł���������ݒ�B
				m_moveDirection = moveDirection;
			}

		private:
			void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

		private:
			CEffectPlayer* m_mainEffect = nullptr;	//���C���̃G�t�F�N�g
			CEffectPlayer* m_endEffect = nullptr;	//�I�����̃G�t�F�N�g
			CPhysicsTriggerObject m_trigger;	//�����蔻��
			CVector3 m_position = CVector3::Zero();	//���W
			CVector3 m_moveDirection = CVector3::Zero();//���ł�������
			float m_durationTime = 0.0f;		//��������

			
		};
	}
}