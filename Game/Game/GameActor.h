#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	class CStatus;
	
	namespace nsFeature{

		class CFeature;
	}
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}
	namespace nsSkill {

		class CPassiveSkill;
	}

	//�Q�[���A�N�^�[
	//�X�e�[�^�X�ω��Ȃǂ�t�^�����
	class IGameActor : public IGameObject
	{
	public:

		void AddStatusChanger(nsFeature::CFeature* statusChanger);

		virtual CStatus* GetStatus() = 0;

		virtual nsWeapon::CWeapon* GetWeapon() = 0;

		virtual nsArmor::CArmor* GetArmor() = 0;

		virtual void ApplyDamage(float power, bool canGuard = true) = 0;

		virtual void HealHP(float healValue) = 0;
		virtual void HealMP(float healValue) = 0;
		virtual void HealSP(float healValue) = 0;

		void AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill);
	protected:

		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
	private:

		void UpdateFeature(float deltaTime);

		void UpdatePassiveSkill();
	private:
		int m_passiveSkillMaxNum = 5;				//�p�b�V�u�X�L���̍ő�\������
		std::list<nsFeature::CFeature*> m_feature;	//�X�e�[�^�X��ω���������̂̃��X�g
		std::list<nsSkill::CPassiveSkill*> m_passiveSkill;	//�p�b�V�u�X�L��
	};
}

