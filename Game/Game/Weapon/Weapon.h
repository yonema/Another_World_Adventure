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

