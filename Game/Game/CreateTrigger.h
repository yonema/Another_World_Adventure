#pragma once

namespace nsAWA {

	//�g���K�[�����N���X
	class CCreateTrigger : public IGameObject
	{
		//�g���K�[�̏��
		struct STriggerInfo {

			float size = 0.0f;	//�T�C�Y
			CVector3 position = CVector3::Zero();	//���W
			std::list<std::vector<std::string>> m_featureList;		//���ʂ̃��X�g
		};
	public:
		void Create(std::list<std::vector<std::string>> triggerMaterial,
			const CVector3& position = CVector3::Zero(),
			const CVector3& forwardDirection = CVector3::Zero()
		);

		void OnDestroy()override final;

		void Update(float deltaTime)override final;

	private:
		void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

	private:
		CPhysicsTriggerObject m_trigger;	//�g���K�[
		STriggerInfo m_triggerInfo;			//�g���K�[�̏��
		float m_triggerDurationTime = 0.0f;	//�g���K�[�̎�������
	};
}