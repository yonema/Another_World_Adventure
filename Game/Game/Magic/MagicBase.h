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

			void SetMagicName(const std::string& name) {

				//���O��ݒ�B
				m_name = name;
			}

			const std::string& GetMagicName()const {

				//���O���擾�B
				return m_name;
			}

			virtual void SetPosition(const CVector3& position) = 0;

			virtual void SetMoveDirection(const CVector3& moveDirection) = 0;

			void SetFeatureList(std::list<std::vector<std::string>> featureList) {

				//���ʂ̃��X�g��ݒ�B
				m_featureList = featureList;
			}

			void ExecuteFeature(IGameActor* target);

		private:
			std::string m_name = "NoName";	//���O
			IGameActor* m_owner = nullptr;	//������
			std::list<std::vector<std::string>> m_featureList;		//���ʂ̃��X�g
		};
	}
}