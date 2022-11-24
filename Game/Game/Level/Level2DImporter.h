#pragma once
#include "Level2DSpriteData.h"

namespace nsAWA
{
	namespace nsLevel
	{
		class Level2DImporter
		{
		public:
			void Load(const char* path, std::function<bool(Level2DSpriteData)> hookFunc = nullptr);

		private:
			CSpriteRenderer* CreateNewSpriteFromData(const Level2DSpriteData& spriteData);

			std::list<CSpriteRenderer*> m_spritesList;
		};
	}
}

