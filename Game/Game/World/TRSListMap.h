#pragma once
namespace nsAWA
{
	namespace nsWorld
	{
		using TRSList = std::list<STRS>;
		using TRSMap = std::unordered_map<std::string, STRS>;
		using TRSListMap = std::unordered_map<std::string, TRSList>;

	}
}