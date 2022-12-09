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
			enGround,
			enWall,
			enPlayer,
			enItemRigidBody

			// ここから下に拡張していってください。
		};
	}
}