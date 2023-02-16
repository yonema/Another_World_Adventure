#pragma once

namespace nsAWA {

	namespace nsArmor {

		//�h����
		struct SArmorInfo {

			std::string name = "NoName";		//���O
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

			void Create(const SArmorInfo& armorInfo);
		public:
			const std::string& GetArmorName()const {

				//�h��̖��O���擾�B
				return m_sInfo.name;
			}

			float GetDeffence()const {

				return m_sInfo.defence;
			}
			void SetDeffence(float deffence) {

				m_sInfo.defence = deffence;
			}

			float GetMind()const {

				return m_sInfo.mind;
			}
			void SetMind(float mind) {

				m_sInfo.mind = mind;
			}
		private:
			SArmorInfo m_sInfo;								//���
		};

		//�h����N���X
		class CArmorBuilder : nsUtils::SNoncopyable {

		public:
			CArmor* CreateArmor(const std::string& armorName);
		};
	}
}


