#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsFeature {

		class CFeature;
	}

	namespace nsSkill {

		//�X�L���N���X
		class CSkill : nsUtils::SNoncopyable
		{
		public:
			virtual void AddFeature(nsFeature::CFeature* feature) = 0;

		protected:
			void Create(nsFeature::CFeature* feature);
		protected:
			const char* m_name = nullptr;					//���O
			std::list<nsFeature::CFeature*> m_featureList;	//���ʂ̃��X�g
		};
	}
}

