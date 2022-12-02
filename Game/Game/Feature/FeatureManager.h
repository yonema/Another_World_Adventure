#pragma once
namespace nsAWA {

	//�O���錾
	namespace nsFeature {

		class CFeature;
	}

	namespace nsFeature {

		//�@�\�Ǘ��N���X
		class CFeatureManager : nsUtils::SNoncopyable
		{
		public:
			void AddStatusChanger(nsFeature::CFeature* statusChanger) {

				//�X�e�[�^�X�ω���t�^�B
				m_feature.emplace_back(statusChanger);
			}

			void UpdateFeature(float deltaTime);

			bool IsParalysis()const {

				//��჏�Ԃ��ǂ������^�[������B
				return m_isParalysis;
			}

			bool IsPoison()const {

				//�ŏ�Ԃ��ǂ������^�[������B
				return m_isPoison;
			}

			bool CanUseActiveSkill();

		private:
			void UpdateFeatureState();
		private:
			std::list<nsFeature::CFeature*> m_feature;	//�X�e�[�^�X��ω���������̂̃��X�g
			bool m_isPoison = false;		//�ŏ�ԁH
			bool m_isParalysis = false;		//��჏�ԁH
		};
	}
}

