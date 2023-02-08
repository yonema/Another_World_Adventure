#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//�p�b�V�u�X�L��
		class CPassiveSkill : public CSkill
		{
		public:
			void SetFeatureListStr(std::list<std::vector<std::string>> featureListStr) {

				//���ʂ̃��X�g�̕������ݒ�B
				m_featureListStr = featureListStr;
			}

			const std::list<std::vector<std::string>>& GetFeatureListStr()const {

				//���ʂ̃��X�g�̕�������擾�B
				return m_featureListStr;
			}

			void SetFeatureList(const std::list<nsFeature::CFeature*>& featureList) {

				//���ʂ̃��X�g��ݒ�B
				m_featureList = featureList;
			}

			std::list<nsFeature::CFeature*>& GetFeatureList() {

				//���ʂ̃��X�g���擾�B
				return m_featureList;
			}

			void Update();

		private:
			std::list<std::vector<std::string>> m_featureListStr;//���ʂ̃��X�g�̕�����
			std::list<nsFeature::CFeature*> m_featureList;		//���ʂ̃��X�g
		};
	}
}

