#pragma once
namespace nsYMEngine
{
	namespace nsPhysics
	{
		/**
		 * @brief 物理属性。物理オブジェクトに設定される属性。
		*/
		enum class EnPhysicsAttributes
		{
			enNone,
			enCharacterController,
			enGround,
			enWall,


			// ここから下に拡張していってください。
			enPlayer,
			enPlayerAttack,
			enMonster,
			enItemRigidBody
		};
	}
}