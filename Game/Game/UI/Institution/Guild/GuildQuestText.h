#pragma once

namespace nsAWA
{
	namespace nsUI
	{
		enum class EnQuestProgress
		{
			enNotReceive,
			enReceive,
			enComplete
		};

		class CGuildQuestText : public IGameObject
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

			void SetQuestName(std::string questName)
			{
				m_questName = questName;
			}
			
			void SetEventOnReceive(std::function<void(void)> eventFunc);

			void SetEventOnClear(std::function<void(void)> eventFunc);

			void SetPosition(const CVector2& position)
			{
				m_fontPosition = position;
			}

			void Select();
		public:
			CGuildQuestText() = default;
			~CGuildQuestText() = default;

		private:
			const CVector2 m_kTextPivot = CVector2(0.0f, 0.5f);
		private:
			CFontRenderer* m_fontRenderer = nullptr;
			std::string  m_questName = "";
			std::function<void(void)> m_onReceiveEvent = nullptr;
			std::function<void(void)> m_onClearEvent = nullptr;
			CVector2 m_fontPosition = CVector2::Zero();
			EnQuestProgress m_questProgress = EnQuestProgress::enNotReceive;
		};
	}
}

