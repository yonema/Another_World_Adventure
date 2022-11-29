#pragma once
#include "../YonemaEngine/Input/InputManagerData.h"



/**
* @file InputMapping.h
* @brief ���z�{�^�����쐬���A�Q�[���p�b�h��L�[�{�[�h�Ɋ��蓖�Ă邽�߂̃}�b�s���O�f�[�^�̃t�@�C��
* @details EnActionMapping��EnAxisMapping�ŁA���͂̎�ނ𑝂₵�܂��B
* g_kActionMappingTable��g_kAxisMappingTable�ő��₵�����̓��͂ɁA�{�^�������蓖�Ă܂��B
*/


namespace nsYMEngine
{
	namespace nsInput
	{
		/**
		 * @brief �A�N�V�����}�b�s���O
		 * �{�^����Trigger��Press���Ăׂ�悤�ɂȂ���̓}�b�s���O
		*/
		enum class EnActionMapping
		{
			enWeakAttack,				//��U��
			enStrongAttack,				//���U��
			enDashPreparation,			//�_�b�V������
			enGuardPreparation,			//�K�[�h����
			enGuard,					//�K�[�h
			enSkillPreparation,			//�X�L������
			enUseSkill_1,				//�X�L���P�g�p
			enUseSkill_2,				//�X�L���Q�g�p
			enUseSkill_3,				//�X�L���R�g�p
			enUseSkill_4,				//�X�L���S�g�p
			enUseSkill_5,				//�X�L���T�g�p
			enUseSkill_6,				//�X�L���U�g�p
			enUseItem,					//�A�C�e���g�p

			enNumActions
		};

		/**
		 * @brief �A�N�V�Y�}�b�s���O
		 * �����͒l�����Ƃ��悤�ɂȂ���̓}�b�s���O
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
		 * @brief �A�N�V�����}�b�s���O�̓��͓��e�̐ݒ�e�[�u��
		*/
		const nsInputManagerData::SActionMapChip
			g_kActionMappingTable[static_cast<int>(EnActionMapping::enNumActions)] =
		{
			//// enExsample	// �A�N�V�����}�b�s���O
			//{
			//	// �Q�[���p�b�h�̃{�^���̊��蓖��
			//	// {���蓖�Ă�Q�[���p�b�h�̉��z�{�^��1, ���蓖�Ă�Q�[���p�b�h�̉��z�{�^��2 ...}
			//	{CGamepad::EnPadButton::enA ,CGamepad::EnPadButton::enB},
			//	// �L�[�{�[�h�̃{�^���̊��蓖��
			//	// {���蓖�Ă�L�[�{�[�h�̉��z�{�^��1, ���蓖�Ă�L�[�{�[�h�̉��z�{�^��2 ...}
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
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseSkill_1
			{
				{CGamepad::EnPadButton::enA},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseSkill_2
			{
				{CGamepad::EnPadButton::enB},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseSkill_3
			{
				{CGamepad::EnPadButton::enX},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseSkill_4
			{
				{CGamepad::EnPadButton::enY},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseSkill_5
			{
				{CGamepad::EnPadButton::enRB1},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseSkill_6
			{
				{CGamepad::EnPadButton::enRB2},
				{CKeyboard::EnKeyButton::enSpace,CKeyboard::EnKeyButton::enLShift}	//��ŕύX
			},
			//enUseItem
			{
				{CGamepad::EnPadButton::enX},
				{CKeyboard::EnKeyButton::enL}
			},
		};

		/**
		 * @brief �A�N�V�Y�}�b�s���O�̓��͓��e�̐ݒ�e�[�u��
		*/
		const nsInputManagerData::SAxisMapChip
			g_kAxisMappingTable[static_cast<int>(EnAxisMapping::enNumAxes)] =
		{
			//// enExsample	// �A�N�V�Y�}�b�s���O
			//{
			//	// �Q�[���p�b�h�̃{�^���̊��蓖��
			//	// {{���蓖�Ă�Q�[���p�b�h�̉��z�{�^��1, �����͂̒l1},{���蓖�Ă�Q�[���p�b�h�̉��z�{�^��2, �����͂̒l2}}
			//	{{CGamepad::EnPadButton::enUp, 1.0f}, {CGamepad::EnPadButton::enDown, -1.0f}},
			//	// �L�[�{�[�h�̃{�^���̊��蓖��
			//	// {{���蓖�Ă�L�[�{�[�h�̉��z�{�^��1, �����͂̒l1},{���蓖�Ă�L�[�{�[�h�̉��z�{�^��2, �����͂̒l2}}
			//	{{CKeyboard::EnKeyButton::enW, 1.0f}, {CKeyboard::EnKeyButton::enS, -1.0f}},
			//	// �Q�[���p�b�h�̎����͂̊��蓖��
			//	// {{���蓖�Ă�Q�[���p�b�h�̉��z������1, �����͂̃X�P�[��1},{���蓖�Ă�Q�[���p�b�h�̉��z������2, �����͂̃X�P�[��2}}
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
			// enCameraUp�i�܂��������j
			{
				{{CGamepad::EnPadButton::enNone, .0f}, {CGamepad::EnPadButton::enNone, .0f}},
				{{CKeyboard::EnKeyButton::enUp, 1.0f},{CKeyboard::EnKeyButton::enDown, -1.0f}},
				{{nsInputManagerData::EnGamepadStickAxis::enRStickY, 1.0f}}
			},
			// enCameraRight�i�܂��������j
			{
				{{CGamepad::EnPadButton::enNone, .0f}, {CGamepad::EnPadButton::enNone, .0f}},
				{{CKeyboard::EnKeyButton::enRight, 1.0f},{CKeyboard::EnKeyButton::enLeft, -1.0f}},
				{{nsInputManagerData::EnGamepadStickAxis::enRStickX, 1.0f}}
			},
		};


	}
}
