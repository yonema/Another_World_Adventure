#pragma once
#include "ProgressManagement/EventProgressManager.h"
#include "../CSV/CSVManager.h"
#include "EventPieceType.h"
#include "../World/TRSListMap.h"

namespace nsAWA
{
	namespace nsPlayer
	{
		class CPlayer;
	}
	namespace nsEvent
	{
		class CEventSetFuncPool;
	}
}
namespace nsAWA
{
	namespace nsEvent
	{
		class CEventManager : nsUtils::SNoncopyable
		{
		private:
			static const wchar_t* const m_kCsvFilePath;
			static const char* const m_kRootEventName;

			enum class EnEventCsvType
			{
				enNone = -1,
				enName,
				enConditions,
				enProgress,
				enNum
			};

			static const char* const m_kEventCsvPrefixArray[static_cast<int>(EnEventCsvType::enNum)];
			static const char* const m_kEventPiecePrefixArray[static_cast<int>(EnEventPieceType::enNum)];

			struct SEventMaterial
			{
				std::string name = {};
				std::list<std::string> conditionsEventNameArray = {};
				std::list<EnEventPieceType> pieceTypeList = {};
			};

			static const char* const m_kLevelFilePath;

		private:
			CEventManager();
			~CEventManager();

		public:
			static CEventManager* CreateInstance()
			{
				if (m_progressManagerInstance == nullptr)
				{
					m_progressManagerInstance = CEventProgressManager::CreateInstance();
				}

				if (m_instance == nullptr)
				{
					m_instance = new CEventManager();
				}
				return m_instance;
			}

			static CEventManager* GetInstance() noexcept
			{
				return m_instance;
			}

			static void DeleteInstance()
			{
				if (m_instance)
				{
					delete m_instance;
					m_instance = nullptr;
				}
				if (m_progressManagerInstance)
				{
					CEventProgressManager::DeleteInstance();
					m_progressManagerInstance = nullptr;
				}
			}

			constexpr const auto& GetEventProgressMap() const noexcept
			{
				return m_eventProgressMap;
			}

			constexpr void SetPlayerRef(nsPlayer::CPlayer* playerRef) noexcept
			{
				m_playerRef = playerRef;
			}

			constexpr const auto* GetPlayerRef() const noexcept
			{
				return m_playerRef;
			}
			
			constexpr const auto& GetEventMaterialMap() const noexcept
			{
				return m_eventMaterialMap;
			}


			constexpr auto& GetEventTriggerMap() const noexcept
			{
				return m_eventTriggerMap;
			}

			constexpr auto& GetEventSetFuncPool() const noexcept
			{
				return m_eventSetFuncPool;
			}

		private:
			void Init();

			void Terminate();

			EnEventCsvType CheckEventCsvType(const std::string& data);

			void InitEventTriggerTRS();

			void PushEventTrigger(const std::string& name, const STRS& trs);


			void PushPieceType(SEventMaterial* eventMatOut, const std::string& data);

		private:
			static CEventManager* m_instance;
			static CEventProgressManager* m_progressManagerInstance;
			nsPlayer::CPlayer* m_playerRef = nullptr;
			nsCSV::CCsvManager m_csvManager = {};
			std::unordered_map<std::string, CEventProgress> m_eventProgressMap = {};
			std::unordered_map<std::string, SEventMaterial> m_eventMaterialMap = {};
			nsWorld::TRSMap m_eventTriggerMap = {};
			CEventSetFuncPool* m_eventSetFuncPool = nullptr;
		};

	}
}