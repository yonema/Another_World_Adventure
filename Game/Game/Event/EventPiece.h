#pragma once
#include "EventPieceType.h"

namespace nsAWA
{
	namespace nsUI
	{
		class CConversationPlayerInputDisable;
	}
}

namespace nsAWA
{
	namespace nsEvent
	{

		class CEventPiece : public IGameObject
		{
		private:
			static const char* const m_kCsvFileRootPath;
			static const float m_kActionDist;

		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CEventPiece() = default;
			~CEventPiece() = default;

			void Init(
				const std::string& eventName, 
				EnEventPieceType pieceType,
				int conversationCount, 
				int triggerCount,
				int setFuncCount
			) noexcept;

			void StartEvent();

			inline void SetClear() noexcept
			{
				if (m_eventPieceType != EnEventPieceType::enSet)
				{
#ifdef _DEBUG
					nsGameWindow::MessageBoxWarning(L"このイベントピースはSetではありません。");
#endif
					return;
				}

				Clear();
			}

			constexpr bool IsClear() const noexcept
			{
				return m_isClear;
			}

			constexpr auto GetPieceType() const noexcept
			{
				return m_eventPieceType;
			}

			inline void SetSetFunc(const std::function<bool(void)>& setFunc)
			{
				m_setFunc = setFunc;
			}

		private:

			constexpr void Clear() noexcept
			{
				m_isClear = true;
			}

			void OnTriggerEnter(CExtendedDataForRigidActor* oterData);

			void UpdateAction(); 

			void UpdateConversation();

			void UpdateSet();

		private:
			std::string m_eventName = {};
			EnEventPieceType m_eventPieceType = EnEventPieceType::enNone;
			int m_conversationCount = -1;
			int m_triggerCount = -1;
			int m_setFuncCount = -1;
			CPhysicsTriggerObject m_trigger = {};
			nsUI::CConversationPlayerInputDisable* m_conversation = nullptr;
			CVector3 m_position = CVector3::Zero();
			bool m_isClear = false;
			std::function<bool(void)> m_setFunc = [](){ return true; };
			bool m_isStartEvent = false;
		};

	}
}