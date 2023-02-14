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
			"���_�ƈِ��E�]��",
			"�������N�`���҂ƏC�s",
			"�A���}�̒�",
			"�`���ғo�^",
			"�򑐍̎�ƃ����X�^�[����",
			"�h�Ɩ`���҃����N�A�b�v",
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