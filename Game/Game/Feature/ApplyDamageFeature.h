#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//�_���[�W��^����@�\
		class CApplyDamageFeature : public CFeature
		{
		public:
			
			/**
			 * @brief �ʏ�_���[�W
			*/
			void Init(IGameActor* creator, IGameActor* target, float power, const std::string& attackType, bool canGuard);

			/**
			 * @brief �Œ�_���[�W
			*/
			void Init(const std::string& damageType, IGameActor* target, float damage, bool canGuard);

			void Create()override final;
		private:
			float m_damage = 0.0f;				//�_���[�W
			float m_level = 0.0f;				//���x��
			float m_power = 0.0f;				//�З�
			float m_attack = 0.0f;				//�U����
			float m_deffence = 0.0f;			//�h���
			bool m_canGuard = true;				//�K�[�h�\�H
		};
	}
}


