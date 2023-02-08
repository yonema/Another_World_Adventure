#pragma once

namespace nsAWA
{
	namespace nsUI
	{
		class CMenuBaseUI;
	}

	//�Q�[���N���X
	class CGame : public IGameObject
	{
	private:
		static const char* const m_kGameObjectName;		//�Q�[���N���X�̖��O

	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	public:
		constexpr CGame() = default;
		~CGame() = default;


	private:
		void TestMenu();

		void TestDeleteMenu();

	private:

		nsUI::CMenuBaseUI* m_menuBaseUI = nullptr;
		bool m_flagCreateMenuBaseUI = false;
	};
}