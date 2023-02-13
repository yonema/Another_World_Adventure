#pragma once
#include "Forge.h"
#include "Guild.h"
#include "Inn.h"
#include "Shop.h"
#include "Town.h"

namespace nsAWA
{
	namespace nsWorld
	{
		enum class EnFacilityType
		{
			enTown,
			enInn,
			enShop,
			enForge,
			enGuild,
			enNum
		};

		constexpr const char* const 
			g_kFacilityNameArray[static_cast<int>(EnFacilityType::enNum)] =
		{
			"Town",
			"Inn",
			"Shop",
			"Forge",
			"Guild",
		};

		constexpr const char* const g_kFacilityCollisionFilePath_Town = 
			"Assets/Models/Town/Facility_Town.fbx";
		constexpr const char* const g_kFacilityCollisionFilePath_Mini =
			"Assets/Models/Town/Facility_Mini.fbx";

	}
}