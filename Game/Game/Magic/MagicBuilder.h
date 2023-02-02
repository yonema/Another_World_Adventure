#pragma once

namespace nsAWA {

	namespace nsMagic {

		//魔法生成クラス
		class CMagicBuilder : public IGameObject
		{
		public:

			void Update(float deltaTime)override final;

			virtual void UpdateSub(float deltaTime) = 0;

			virtual void Execute() = 0;
		};
	}
}