#pragma once

namespace nsAWA {

	namespace nsMagic {

		//–‚–@¶¬ƒNƒ‰ƒX
		class CMagicBuilder : public IGameObject
		{
		public:

			void Update(float deltaTime)override final;

			virtual void UpdateSub(float deltaTime) = 0;

			virtual void Execute() = 0;
		};
	}
}