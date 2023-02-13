#pragma once

namespace nsAWA {

	//�O���錾
	class CStatus;
	class CGameActorCollider;
	
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

		virtual bool IsDeath()const = 0;

		void SetHitStop(bool flag) {

			//�q�b�g�X�g�b�v�̃t���O��ݒ�B
			m_isHitStop = flag;
		}

		bool IsHitStop()const {

			//�q�b�g�X�g�b�v�̃t���O���擾�B
			return m_isHitStop;
		}

	protected:
		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}

	public:
		virtual CStatus* GetStatus() = 0;

		void SetPosition(const CVector3& position) {

			//���W��ݒ�B
			m_position = position;
		}

		const CVector3& GetPosition()const {

			//���W���擾�B
			return m_position;
		}

		void SetPositionOffset(const CVector3& offset) {

			//���W���I�t�Z�b�g��ݒ�B
			m_positionOffset = offset;
		}

		const CVector3& GetPositionOffset()const {

			//���W�̃I�t�Z�b�g���擾�B
			return m_positionOffset;
		}

		const CVector3& GetPositionAndPositionOffset()const {

			//���W���I�t�Z�b�g���݂Ŏ擾�B
			return m_position + m_positionOffset;
		}

		void SetRotation(const CQuaternion& rotation) {

			//��]��ݒ�B
			m_rotation = rotation;
		}

		const CQuaternion& GetRotation()const {

			//��]���擾�B
			return m_rotation;
		}

		void UpdateForwardDirection();

		const CVector3& GetForwardDirection()const {

			//�O�������擾�B
			return m_forwardDirection;
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

		virtual CGameActorCollider* GetGameActorCollider() = 0;

		CModelRenderer* GetModelRenderer() {

			//���f�����擾�B
			return m_modelRenderer;
		}
	protected:
		CModelRenderer* m_modelRenderer = nullptr;	//���f��
		CVector3 m_position = CVector3::Zero();		//���W
		CVector3 m_forwardDirection = CVector3::Zero();		//�O����
		CQuaternion m_rotation = CQuaternion::Identity();	//��]
		CVector3 m_positionOffset = CVector3::Zero();//���W�̃I�t�Z�b�g
		bool m_isHitStop = false;						//�q�b�g�X�g�b�v���H

	private:
		nsSkill::CPassiveSkillManager* m_passiveSkillManager = nullptr;		//�p�b�V�u�X�L���Ǘ�
		nsFeature::CFeatureManager* m_featureManager = nullptr;		//�X�e�[�^�X�ω��Ǘ�
	};
}

