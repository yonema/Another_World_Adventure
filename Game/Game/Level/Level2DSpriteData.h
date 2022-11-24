#pragma once

namespace nsAWA
{
	namespace nsLevel
	{
		class Level2DSpriteData
		{
		private:
			//���̃J���[�\���́@�ォ������܂�
			struct Color
			{
				int a = 255;
				int r = 255;
				int g = 255;
				int b = 255;
			};
		public:
			std::string Path = "";
			std::string Name = "";
			CVector2 SpriteSize;
			CVector2 Position;
			float RotateDeg = 0.0f;
			CVector2 Scale;
			CVector4 MulColor;
			CVector2 Pivot;
			int Priority = 0;
		};
	}
}