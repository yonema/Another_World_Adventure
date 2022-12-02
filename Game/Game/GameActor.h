#pragma once

namespace nsAWA {

	//�O���錾
	class CStatus;
	
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}
	namespace nsFeature{

		class CFeatureManager;
	}
	
	namespace nsSkill {

		class CPassiveSkillManager;
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

		virtual void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true) = 0;

		virtual void HealHP(float healValue) = 0;
		virtual void HealMP(float healValue) = 0;
		virtual void HealSP(float healValue) = 0;

	protected:
		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
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

		nsSkill::CPassiveSkillManager* GetPassiveSkillManager() {

			//�p�b�V�u�X�L���Ǘ��N���X����������Ă��Ȃ��Ȃ�B
			if (m_passiveSkillManager == nullptr) {

				//�x�����o���B
				nsGameWindow::MessageBoxError(L"�p�b�V�u�X�L���Ǘ��N���X����������Ă��܂���B");
			}

			//�p�b�V�u�X�L���ɃA�N�Z�X���邽�߂ɁA�Ǘ��N���X���擾�B
			return m_passiveSkillManager;
		}

		nsFeature::CFeatureManager* GetFeatureManager() {

			//�X�e�[�^�X�ω��Ǘ��N���X����������Ă��Ȃ��Ȃ�B
			if (m_featureManager == nullptr) {

				//�x�����o���B
				nsGameWindow::MessageBoxError(L"�X�e�[�^�X�ω��Ǘ��N���X����������Ă��܂���B");
			}

			//�X�e�[�^�X�ω��̃��X�g�ɃA�N�Z�X���邽�߂ɁA�Ǘ��N���X���擾�B
			return m_featureManager;
		}
	private:
		nsItem::CItemManager* m_itemManager = nullptr;		//�A�C�e���Ǘ�
		nsSkill::CPassiveSkillManager* m_passiveSkillManager = nullptr;		//�p�b�V�u�X�L���Ǘ�
		nsFeature::CFeatureManager* m_featureManager = nullptr;		//�X�e�[�^�X�ω��Ǘ�
	};
}

