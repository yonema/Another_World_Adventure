#pragma once
namespace nsAWA
{
	namespace nsEvent
	{
		enum class EnEventNameType
		{
			enGoddesAndAWTransfer,
			enTrainingWithHRA,
			enTownOfAlma,
			enRegisterAdventurer,
			enHerbAndSlayMonster,
			enInnAndRankUp,
			enNum
		};

		constexpr const char* const g_kEventNameTable[static_cast<int>(EnEventNameType::enNum)] =
		{
			"—_‚ÆˆÙ¢ŠE“]ˆÚ",
			"‚ƒ‰ƒ“ƒN–`Œ¯Ò‚ÆCs",
			"ƒAƒ‹ƒ}‚Ì’¬",
			"–`Œ¯Ò“o˜^",
			"–ò‘Ìæ‚Æƒ‚ƒ“ƒXƒ^[“¢”°",
			"h‚Æ–`Œ¯Òƒ‰ƒ“ƒNƒAƒbƒv",
		};

		constexpr const char* const GetEventNameFromTable(EnEventNameType eventNameType)
		{
			return g_kEventNameTable[static_cast<int>(eventNameType)];
		}

		static const std::unordered_map<std::string, const char* const> g_kEventNameEngToJpMap =
		{
			{"TrainingWithHRA", GetEventNameFromTable(EnEventNameType::enTrainingWithHRA)},
			{"TownOfAlma", GetEventNameFromTable(EnEventNameType::enTownOfAlma)},
		};




	}
}