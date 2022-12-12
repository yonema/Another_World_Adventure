#pragma once

namespace nsAWA {

	namespace nsWeapon {

		//����̎��
		enum class EnWeaponType {

			enSword,	//��
			enAxe,		//��
			enWand,		//��

			enNum,		//���퐔
			enNone		//�ݒ�Ȃ�
		};

		//������
		struct SWeaponInfo {

			EnWeaponType weaponType = EnWeaponType::enNone;	//����̎��
			const char* name = nullptr;		//���O
			float attack = 0.0f;			//�����U����
			float intelligence = 0.0f;		//���@�U����
			float critical = 0.0f;			//�N���e�B�J����
		};

		//����N���X
		class CWeapon : nsUtils::SNoncopyable
		{
			//���퐶���N���X�̓t�����h
			friend class CWeaponBuilder;
		public:

			void Release();
		private:

			void Create(const SWeaponInfo& weaponInfo, const char* modelFilePath);

			void CreateModel(const char* modelFilePath);

		public:
			void SetAttack(float attack) {

				m_sInfo.attack = attack;
			}
			float GetAttack()const {

				return m_sInfo.attack;
			}

			void SetIntelligence(float intelligence) {

				m_sInfo.intelligence = intelligence;
			}
			float GetIntelligence()const {

				return m_sInfo.intelligence;
			}

			void SetCritical(float critical) {

				m_sInfo.critical = critical;
			}
			float GetCritical()const {

				return m_sInfo.critical;
			}

			void SetPosition(const CVector3& position) {

				//���W��ݒ�B
				m_modelRenderer->SetPosition(position);
			}

			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_modelRenderer->GetPosition();
			}

			void SetRotation(const CQuaternion& rotation) {

				//��]��ݒ�B
				m_modelRenderer->SetRotation(rotation);
			}

			const CQuaternion& GetRotation()const {

				//��]���擾�B
				return m_modelRenderer->GetRotation();
			}

			void SetScale(const CVector3& scale) {

				//�g�嗦��ݒ�B
				m_modelRenderer->SetScale(scale);
			}

			const CVector3& GetScale()const {

				//�g�嗦���擾�B
				m_modelRenderer->GetScale();
			}


		private:
			
			CModelRenderer* m_modelRenderer = nullptr;		//���f��
			SWeaponInfo m_sInfo;							//���
		};

		//���퐶���N���X
		class CWeaponBuilder : nsUtils::SNoncopyable {

		public:
			CWeapon* Create(const SWeaponInfo& weaponInfo, const char* modelFilePath);
		};
	}
}

