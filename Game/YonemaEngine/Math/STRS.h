#pragma once
namespace nsYMEngine
{
	namespace nsMath
	{
		struct STRS
		{
			constexpr STRS() = default;
			STRS(const CVector3& pos, const CQuaternion& rot, const CVector3& scale)
				:pos(pos), rot(rot), scale(scale)
			{};
			~STRS() = default;


			CMatrix CalcMatrix() const noexcept
			{
				CMatrix mTrans, mRot, mScale;
				mTrans.MakeTranslation(pos);
				mRot.MakeRotationFromQuaternion(rot);
				mScale.MakeScaling(scale);

				return mScale * mRot * mTrans;
			}

			CVector3 pos = CVector3::Zero();
			CQuaternion rot = CQuaternion::Identity();
			CVector3 scale = CVector3::One();
		};
	}
}