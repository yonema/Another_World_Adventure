#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	class CStatus;
	namespace nsStatusChanger {

		class CStatusChanger;
	}

	//�Q�[���A�N�^�[
	//�X�e�[�^�X�ω��Ȃǂ�t�^�����
	class IGameActor : public IGameObject
	{
	public:

		void AddStatusChanger(nsStatusChanger::CStatusChanger* statusChanger);

		virtual CStatus* GetStatus() = 0;

		virtual void ApplyDamage(float power, bool canGuard = true) = 0;
	protected:

		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
	private:

		void UpdateStatusChanger(float deltaTime);
	private:
		std::list<nsStatusChanger::CStatusChanger*> m_statusChanger;	//�X�e�[�^�X��ω���������̂̃��X�g
	};
}

