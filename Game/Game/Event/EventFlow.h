#pragma once
#include "EventPiece.h"
namespace nsAWA
{
	namespace nsEvent
	{
		class CEventFlow : public IGameObject
		{
		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CEventFlow() = default;
			~CEventFlow() = default;

			void Init(const std::string& eventName);

			inline void SetSetFunc(int setIdx, const std::function<bool(void)>& setFunc)
			{
				m_setPieceArray.at(setIdx)->SetSetFunc(setFunc);
			}

			inline void SetCurrentClear() noexcept
			{
				m_eventPieceArray.at(m_currentPieceIdx)->SetClear();
			}

			constexpr int GetCurrentPieceIdx() const noexcept
			{
				return m_currentPieceIdx;
			}

			inline auto* GetCurrentPiece() noexcept
			{
				return m_eventPieceArray.at(GetCurrentPieceIdx());
			}

			inline EnEventPieceType GetCurrentPieceType() const noexcept
			{
				return m_eventPieceArray.at(GetCurrentPieceIdx())->GetPieceType();
			}

			constexpr bool IsClear() const noexcept
			{
				return m_isClear;
			}

			void Release();

		private:
			std::string m_eventName = {};
			std::vector<CEventPiece*> m_eventPieceArray = {};
			std::vector<CEventPiece*> m_setPieceArray = {};
			int m_currentPieceIdx = 0;
			const std::list<EnEventPieceType>* m_pieceTypeListRef = nullptr;
			bool m_isClear = false;
		};

	}
}