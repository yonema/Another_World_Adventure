#include "YonemaEnginePreCompile.h"
#include "SpriteLevelTestScene.h"
#include "../Level/Level2DImporter.h"

namespace nsAWA
{
	namespace nsScenes
	{
		bool SpriteLevelTestScene::Start()
		{
			nsAWA::nsLevel::Level2DImporter levelImporter;
			levelImporter.Load("Assets/2DLevel/LevelFiles/TestSpriteLevel.tdl", [](const nsLevel::Level2DSpriteData& spriteData)->bool
				{
					//Hook

					if (spriteData.Name == "hoge")
					{
						//Do something
						
						return true;
					}

					return false;
				}
			);
			return true;
		}

		void SpriteLevelTestScene::OnDestroy()
		{
		}

		void SpriteLevelTestScene::Update(float deltaTime)
		{
		}
	}
}
