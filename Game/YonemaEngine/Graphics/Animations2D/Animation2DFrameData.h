#pragma once
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsAnimations2D
		{
			struct SAnimation2DFrameData
			{
				CVector2 Position = CVector2(0.0f,0.0f);			//座標
				float RotateDeg = 0.0f;								//回転角度
				CVector2 Scale = CVector2(1.0f, 1.0f);				//拡大率
				CVector4 MulColor = CVector4(1.0f, 1.0f,1.0f,1.0f);	//乗算カラー
				CVector2 Pivot = CVector2(0.5f, 0.5f);				//ピボット
			};
		}
	}
}

