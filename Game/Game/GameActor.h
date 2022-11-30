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
	namespace nsItem {

		class CItemManager;
	}

	//�Q�[���A�N�^�[
	//�X�e�[�^�X�ω��Ȃǂ�t�^�����
	class IGameActor : public IGameObject
	{
	public:
		bool Start()override final;

		void OnDestroy()override final;

		virtual bool StartSub() { return true; }
		
		virtual void OnDestroySub() {};
		
		void AddStatusChanger(nsFeature::CFeature* statusChanger);

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
	public:
		virtual CStatus* GetStatus() = 0;

		virtual nsWeapon::CWeapon* GetWeapon() = 0;

		virtual nsArmor::CArmor* GetArmor() = 0;

		nsItem::CItemManager* GetItemManager() {

			//�A�C�e���Ǘ��N���X����������Ă��Ȃ��Ȃ�B
			if (m_itemManager == nullptr) {

				//�x�����o���B
				nsGameWindow::MessageBoxError(L"�A�C�e���Ǘ��N���X����������Ă��܂���B");
			}

			//�A�C�e���ɃA�N�Z�X���邽�߂ɁA�Ǘ��N���X���擾�B
			return m_itemManager;
		}
	private:
		int m_passiveSkillMaxNum = 5;				//�p�b�V�u�X�L���̍ő�\������
		std::list<nsFeature::CFeature*> m_feature;	//�X�e�[�^�X��ω���������̂̃��X�g
		std::list<nsSkill::CPassiveSkill*> m_passiveSkill;	//�p�b�V�u�X�L��
		nsItem::CItemManager* m_itemManager = nullptr;		//�A�C�e���Ǘ�
	};
}

