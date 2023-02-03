#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;

	namespace nsMagic {

		//���@�N���X�̃x�[�X
		class CMagicBase : public IGameObject
		{
		public:
			void SetOwner(IGameActor* owner) {

				//�����҂�ݒ�B
				m_owner = owner;
			}

			IGameActor* GetOwner()const {

				//�����҂��擾�B
				return m_owner;
			}

			void SetMagicName(const std::string& name) {

				//���O��ݒ�B
				m_name = name;
			}

			const std::string& GetMagicName()const {

				//���O���擾�B
				return m_name;
			}

			void SetPosition(const CVector3& position) {

				//���W��ݒ�B
				m_position = position;
			}

			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_position;
			}

			void SetMoveDirection(const CVector3& moveDirection) {

				//���ł���������ݒ�B
				m_moveDirection = moveDirection;
			}

			const CVector3& GetMoveDirection()const {

				//���ł����������擾�B
				return m_moveDirection;
			}

			void SetFeatureList(std::list<std::vector<std::string>> featureList) {

				//���ʂ̃��X�g��ݒ�B
				m_featureList = featureList;
			}

			const std::list<std::vector<std::string>>& GetFeatureList()const {

				//���ʂ̃��X�g���擾�B
				return m_featureList;
			}

			void ExecuteFeature(IGameActor* target);

		private:
			std::string m_name = "NoName";	//���O
			CVector3 m_position = CVector3::Zero();	//���W
			CVector3 m_moveDirection = CVector3::Zero();//���ł�������
			IGameActor* m_owner = nullptr;	//������
			std::list<std::vector<std::string>> m_featureList;		//���ʂ̃��X�g
		};
	}
}