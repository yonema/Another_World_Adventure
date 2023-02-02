#pragma once

namespace nsAWA {

	namespace nsMagic {

		//�^���������ł������@�i�P�j
		class CMagicBallOne : public IGameObject
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void Init(
				std::string name,
				const CVector3& position,
				const CVector3& moveDirection
			) {
				//�f�[�^���������B
				m_name = name;
				SetPosition(position);
				SetMoveDirection(moveDirection);
			}

			void SetPosition(const CVector3& position) {

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
			std::string m_name = "NoName";			//�G�t�F�N�g�̖��O
			CEffectPlayer* m_mainEffect = nullptr;	//���C���̃G�t�F�N�g
			CEffectPlayer* m_endEffect = nullptr;	//�I�����̃G�t�F�N�g
			CPhysicsTriggerObject m_trigger;	//�����蔻��
			CVector3 m_position = CVector3::Zero();	//���W
			CVector3 m_moveDirection = CVector3::Zero();//���ł�������
			float m_durationTime = 0.0f;		//��������

			std::list<std::vector<std::string>> m_featureList;		//���ʂ̃��X�g
		};
	}
}