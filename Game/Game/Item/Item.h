#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsFeature {

		class CFeature;
	}

	namespace nsItem {

		//�A�C�e���N���X
		class CItem : public IGameObject
		{
		public:

			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			virtual void Use() = 0;

			void AddFeature(nsFeature::CFeature* feature) {

				//���ʂ����X�g�ɒǉ��B
				m_featureList.emplace_back(feature);
			}

		protected:
			void ExecuteFeature();

		public:
			void SetName(const char* name) {

				//���O��ݒ�B
				m_name = name;
			}

			const char* GetName()const {

				//���O���擾�B
				return m_name;
			}

		private:
			const char* m_name = nullptr;	//���O
			CModelRenderer* m_itemModel = nullptr;	//���f��
			CQuaternion m_rotation = CQuaternion::Identity();	//���f���̉�]

			std::list<nsFeature::CFeature*> m_featureList;	//���ʂ̃��X�g
			float m_getValidTimer = 0.0f;	//�擾�L�����ԃ^�C�}�[
			bool m_isGet = false;	//�擾����Ă���H
		};
	}
}

