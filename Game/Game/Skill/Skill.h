#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsFeature {

		class CFeature;
	}

	namespace nsSkill {

		//�X�L���N���X
		class CSkill : nsUtils::SNoncopyable
		{
		public:

			void SetName(const std::string& name) {

				//���O��ݒ�B
				m_name = name;
			}

			const std::string& GetName()const {

				//���O���擾�B
				return m_name;
			}

		protected:
			void Create(nsFeature::CFeature* feature);

		protected:
			std::string m_name = "NoName";					//���O
		};
	}
}

