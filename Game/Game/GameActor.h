#pragma once
#include "Status.h"

namespace nsAWA {

	namespace nsAbnormalStatus {

		class CAbnormalStatus;
	}
	//�Q�[���A�N�^�[
	//��Ԉُ�Ȃǂ�t�^�����
	class IGameActor : public IGameObject
	{
	public:

		void AddAbnormalStatus(nsAbnormalStatus::CAbnormalStatus* abnormalStatus);

		virtual CStatus* GetStatus() = 0;

		virtual void ApplyDamage(float power, bool canGuard = true) = 0;
	protected:

		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
	private:

		void UpdateAbnormalStatus(float deltaTime);
	private:
		std::list<nsAbnormalStatus::CAbnormalStatus*> m_abnormalStatus;		//��Ԉُ�
	};
}

