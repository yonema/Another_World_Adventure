#pragma once
#include "../../CSV/CSVManager.h"
#include "MonsterPopInfo.h"

namespace nsAWA
{
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			class CMonsterPopPoint;
		}
	}
	namespace nsHumans
	{
		class CHumanManager;
	}
}

namespace nsAWA
{
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			class CMonsterPopManager : public IGameObject
			{
			public:
				enum class EnAreaType
				{
					enMeadow,
					enMountain,
					enForest,
					enNum
				};

				static const char* const m_kAreaNameArray[static_cast<int>(EnAreaType::enNum)];
				static const char* const m_kMonsterPopPrefix;

			private:
				static const wchar_t* const m_kCsvFilePath;

			public:
				bool Start() override final;

				void OnDestroy() override final;

				void Update(float deltaTime) override final;

			public:
				CMonsterPopManager();
				~CMonsterPopManager() = default;

				constexpr void SetHumanManagerRef(const nsHumans::CHumanManager& humanManager)
				{
					m_humanManagerRef = &humanManager;
				}

				constexpr const auto* GetHumanManagerRef() const noexcept
				{
					return m_humanManagerRef;
				}

				void GenerateMonsterPopPoint(const std::string& pointName, const CVector3& pos);

			private:
				void LoadData();

				void MessageErrorCsvData(
					const std::vector<std::string>& errorData,
					const char* message
				) const;

				void MessageErrorLevelData(
					const std::string& errorData,
					const char* message
				)const;

				void MessageErrorData(
					const char* preMessage,
					const char* message,
					const std::string& errorData
				) const;

			private:
				nsCSV::CCsvManager m_scvManager = {};
				MnsPopAreaToPoint m_monsterPopInfoTable = {};
				std::list<CMonsterPopPoint*> m_popPointList = {};
				const nsHumans::CHumanManager* m_humanManagerRef;
			};

		}
	}
}