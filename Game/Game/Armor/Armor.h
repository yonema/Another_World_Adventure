#pragma once

namespace nsAWA {

	namespace nsArmor {

		//�h����
		struct SArmorInfo {

			const char* name = nullptr;		//���O
			float defence = 0.0f;			//�����h���
			float mind = 0.0f;				//���@�h���
		};

		//�h��N���X
		class CArmor : nsUtils::SNoncopyable
		{
			//�h����N���X�̓t�����h
			friend class CArmorBuilder;
		public:

			void Release();
		private:

			void Create(const SArmorInfo& armorInfo, const char* modelFilePath);

			void CreateModel(const char* modelFilePath);
		private:

			CModelRenderer* m_modelRenderer = nullptr;		//���f��
			SArmorInfo m_info;								//���
		};

		//�h����N���X
		class CArmorBuilder : nsUtils::SNoncopyable {

		public:
			CArmor* Create(const SArmorInfo& armorInfo, const char* modelFilePath);
		};
	}
}


