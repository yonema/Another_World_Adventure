#pragma once
namespace nsAWA
{
	namespace nsMonster
	{
		namespace nsMonsterPop
		{
			struct SMonsterPopInfo
			{
				SMonsterPopInfo(const std::list<const char*>& nameList, int rate) noexcept
				{
					nameArray.reserve(nameList.size());
					for (const auto& name : nameList)
					{
						nameArray.emplace_back(name);
					}
					popRate = rate;
				}
				~SMonsterPopInfo() = default;

				std::vector<std::string> nameArray = {};
				int popRate = 0;
			};

			using MnsPopInfoList = std::list<SMonsterPopInfo>;
			using MnsPopPointToInfo = std::unordered_map<int, MnsPopInfoList>;
			using MnsPopAreaToPoint = std::unordered_map<std::string, MnsPopPointToInfo>;

		}


	}
}