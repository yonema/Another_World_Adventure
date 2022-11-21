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

				m_info.attack = attack;
			}
			float GetAttack()const {

				return m_info.attack;
			}

			void SetIntelligence(float intelligence) {

				m_info.intelligence = intelligence;
			}
			float GetIntelligence()const {

				return m_info.intelligence;
			}

			void SetCritical(float critical) {

				m_info.critical = critical;
			}
			float GetCritical()const {

				return m_info.critical;
			}


		private:
			
			CModelRenderer* m_modelRenderer = nullptr;		//���f��
			SWeaponInfo m_info;								//���
		};

		//���퐶���N���X
		class CWeaponBuilder : nsUtils::SNoncopyable {

		public:
			CWeapon* Create(const SWeaponInfo& weaponInfo, const char* modelFilePath);
		};
	}
}

