#pragma once

namespace nsAWA {

	//エイリアス宣言
	class CStatus;
	namespace nsStatusChanger {

		class CStatusChanger;
	}

	//ゲームアクター
	//ステータス変化などを付与される
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
		std::list<nsStatusChanger::CStatusChanger*> m_statusChanger;	//ステータスを変化させるもののリスト
	};
}

