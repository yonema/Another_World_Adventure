#pragma once
namespace nsAWA
{
	namespace nsHumans
	{
		enum class EnHumanAnimType
		{
			enIdle,
			enWalk,
			//enRun,
			////enForwardStep,
			//enWeakAttackA,
			//enWeakAttackB,
			//enWeakAttackC,
			////enStrongAttack,
			//enDamage,
			//enDeath,
			////enGuard,
			//enUseItem,
			////enStun,
			////enJumpAttack,
			//enMagic,
			enNum
		};

		constexpr const char* const g_kAnimFilePaths[static_cast<int>(EnHumanAnimType::enNum)] =
		{
			"Assets/Animations/Player/Sword_Idle.fbx",
			"Assets/Animations/Player/Sword_Walk.fbx",
			//"Assets/Animations/Player/Sword_Run.fbx",
			////"Assets/Animations/Player/Sword_ForwardStep.fbx",
			//"Assets/Animations/Player/Sword_WeakAttack_A.fbx",
			//"Assets/Animations/Player/Sword_WeakAttack_B.fbx",
			//"Assets/Animations/Player/Sword_WeakAttack_C.fbx",
			////"Assets/Animations/Player/Sword_StrongAttack.fbx",
			//"Assets/Animations/Player/Sword_Damage.fbx",
			//"Assets/Animations/Player/Sword_Death.fbx",
			////"Assets/Animations/Player/Sword_Guard.fbx",
			//"Assets/Animations/Player/Sword_UseItem.fbx",
			////"Assets/Animations/Player/Sword_Stun.fbx",
			////"Assets/Animations/Player/Sword_JumpAttack.fbx",
			//"Assets/Animations/Player/Magic.fbx"
		};

	}
}