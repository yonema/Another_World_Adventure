#pragma once
#include "../YonemaEngine/Input/InputManagerData.h"



/**
* @file InputMapping.h
* @brief 仮想ボタンを作成し、ゲームパッドやキーボードに割り当てるためのマッピングデータのファイル
* @details EnActionMappingやEnAxisMappingで、入力の種類を増やします。
* g_kActionMappingTableとg_kAxisMappingTableで増やした分の入力に、ボタンを割り当てます。
*/


namespace nsYMEngine
{
	namespace nsInput
	{
		/**
		 * @brief アクションマッピング
		 * ボタンのTriggerやPressが呼べるようになる入力マッピング
		*/
		enum class EnActionMapping
		{
			enWeakAttack,				//弱攻撃
			enStrongAttack,				//強攻撃
			enDashPreparation,			//ダッシュ準備
			enGuardPreparation,			//ガード準備
			enGuard,					//ガード
			enSkillPreparation,			//スキル準備
			enUseSkill_1,				//スキル１使用
			enUseSkill_2,				//スキル２使用
			enUseSkill_3,				//スキル３使用
			enUseSkill_4,				//スキル４使用
			enUseSkill_5,				//スキル５使用
			enUseSkill_6,				//スキル６使用
			enUseItem,					//アイテム使用

			enNumActions
		};

		/**
		 * @brief アクシズマッピング
		 * 軸入力値をがとれるようになる入力マッピング
		*/
		enum class EnAxisMapping
		{
			enForward,
			enRight,
			enCameraUp,
			enCameraRight,
			enNumAxes
		};

		/**
		 * @brief アクションマッピングの入力内容の設定テーブル
		*/
		const nsInputManagerData::SActionMapChip
			g_kActionMappingTable[static_cast<int>(EnActionMapping::enNumActions)] =
		{
			//// enExsample	// アクションマッピング
			//{
			//	// ゲームパッドのボタンの割り当て
			//	// {割り当てるゲームパッドの仮想ボタン1, 割り当てるゲームパッドの仮想ボタン2 ...}
			//	{CGamepad::EnPadButton::enA ,CGamepad::EnPadButton::enB},
			//	// キーボードのボタンの割り当て
			//	// {割り当てるキーボードの仮想ボタン1, 割り当てるキーボードの仮想ボタン2 ...}
			//	{CKeyboard::EnKeyButton::enEnter,CKeyboard::EnKeyButton::enSpace }
			//},


			// enWeakAttack
			{
				{CGamepad::EnPadButton::enB},
				{CKeyboard::EnKeyButton::enK}
			},
			// enStrongAttack
			{
				{CGamepad::EnPadButton::enY},
				{CKeyboard::EnKeyButton::enI}
			},
			//enDashPreparation
			{
				{CGamepad::EnPadButton::enRB1},
				{CKeyboard::EnKeyButton::en7}
			},
			// enGuardPreparation
			{
				{CGamepad::EnPadButton::enRB1},
				{CKeyboard::EnKeyButton::en7}
			},
			// enGuard
			{
				{CGamepad::EnPadButton::enB},
				{CKeyboard::EnKeyButton::enK}
			},
			//enSkillPreparation
			{
				{CGamepad::EnPadButton::enLB1},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseSkill_1
			{
				{CGamepad::EnPadButton::enA},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseSkill_2
			{
				{CGamepad::EnPadButton::enB},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseSkill_3
			{
				{CGamepad::EnPadButton::enX},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseSkill_4
			{
				{CGamepad::EnPadButton::enY},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseSkill_5
			{
				{CGamepad::EnPadButton::enRB1},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseSkill_6
			{
				{CGamepad::EnPadButton::enRB2},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//後で変更
			},
			//enUseItem
			{
				{CGamepad::EnPadButton::enX},
				{CKeyboard::EnKeyButton::enL}
			},
		};

		/**
		 * @brief アクシズマッピングの入力内容の設定テーブル
		*/
		const nsInputManagerData::SAxisMapChip
			g_kAxisMappingTable[static_cast<int>(EnAxisMapping::enNumAxes)] =
		{
			//// enExsample	// アクシズマッピング
			//{
			//	// ゲームパッドのボタンの割り当て
			//	// {{割り当てるゲームパッドの仮想ボタン1, 軸入力の値1},{割り当てるゲームパッドの仮想ボタン2, 軸入力の値2}}
			//	{{CGamepad::EnPadButton::enUp, 1.0f}, {CGamepad::EnPadButton::enDown, -1.0f}},
			//	// キーボードのボタンの割り当て
			//	// {{割り当てるキーボードの仮想ボタン1, 軸入力の値1},{割り当てるキーボードの仮想ボタン2, 軸入力の値2}}
			//	{{CKeyboard::EnKeyButton::enW, 1.0f}, {CKeyboard::EnKeyButton::enS, -1.0f}},
			//	// ゲームパッドの軸入力の割り当て
			//	// {{割り当てるゲームパッドの仮想軸入力1, 軸入力のスケール1},{割り当てるゲームパッドの仮想軸入力2, 軸入力のスケール2}}
			//	{{nsInputManagerData::EnGamepadStickAxis::enLStickY, 1.0f}, {nsInputManagerData::EnGamepadStickAxis::enRStickY, -1.0f}}
			//},
			

			// enForward
			{
				{{CGamepad::EnPadButton::enUp, 1.0f}, {CGamepad::EnPadButton::enDown, -1.0f}},
				{{CKeyboard::EnKeyButton::enW, 1.0f}, {CKeyboard::EnKeyButton::enS, -1.0f}},
				{{nsInputManagerData::EnGamepadStickAxis::enLStickY, 1.0f}}
			},
			// enRight
			{
				{{CGamepad::EnPadButton::enLeft, -1.0f}, {CGamepad::EnPadButton::enRight, 1.0f}},
				{{CKeyboard::EnKeyButton::enA, -1.0f},{CKeyboard::EnKeyButton::enD, 1.0f}},
				{{nsInputManagerData::EnGamepadStickAxis::enLStickX, 1.0f}}
			},
			// enCameraUp（まだ未完成）
			{
				{{CGamepad::EnPadButton::enNone, .0f}, {CGamepad::EnPadButton::enNone, .0f}},
				{{CKeyboard::EnKeyButton::enUp, 1.0f},{CKeyboard::EnKeyButton::enDown, -1.0f}},
				{{nsInputManagerData::EnGamepadStickAxis::enRStickY, 1.0f}}
			},
			// enCameraRight（まだ未完成）
			{
				{{CGamepad::EnPadButton::enNone, .0f}, {CGamepad::EnPadButton::enNone, .0f}},
				{{CKeyboard::EnKeyButton::enRight, 1.0f},{CKeyboard::EnKeyButton::enLeft, -1.0f}},
				{{nsInputManagerData::EnGamepadStickAxis::enRStickX, 1.0f}}
			},
		};


	}
}
