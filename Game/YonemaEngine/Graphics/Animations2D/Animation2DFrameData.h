#pragma once
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsAnimations2D
		{
			struct SAnimation2DFrameData
			{
				CVector2 Position = CVector2(0.0f,0.0f);			//���W
				float RotateDeg = 0.0f;								//��]�p�x
				CVector2 Scale = CVector2(1.0f, 1.0f);				//�g�嗦
				CVector4 MulColor = CVector4(1.0f, 1.0f,1.0f,1.0f);	//��Z�J���[
				CVector2 Pivot = CVector2(0.5f, 0.5f);				//�s�{�b�g
			};
		}
	}
}

