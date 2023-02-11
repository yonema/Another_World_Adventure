#include "FacilityBase.h"
namespace nsAWA
{
	namespace nsFacility
	{
		IFacilityBase::~IFacilityBase()
		{
			Terminate();
			return;
		}

		void IFacilityBase::Terminate()
		{
			m_trigger.Release();

			return;
		}

		bool IFacilityBase::Init(
			const CVector3& position,
			const CQuaternion& rot,
			const CVector3& scale,
			const char* collisionModelFilePath,
			EnPhysicsAttributes attribute
		)
		{
			// コリジョンモデルを生成する

			nsPhysics::SMeshGeometryBuffer physiceMeshGeomBuffer;

			SModelInitData modelInitData;
			modelInitData.modelFilePath = collisionModelFilePath;
			modelInitData.physicsMeshGeomBuffer = &physiceMeshGeomBuffer;

			auto* mr = NewGO<CModelRenderer>();
			// 一瞬たりとも表示させない
			mr->SetScale(0.0f);
			mr->Init(modelInitData);
			// モデルは必要ないからすぐに破棄
			DeleteGO(mr);


			// コリジョンモデルから最小座標、最大座標を求める。

			CVector3 vMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			CVector3 vMin(FLT_MAX, FLT_MAX, FLT_MAX);

			for (const auto& vert : physiceMeshGeomBuffer.m_vertices)
			{
				vMax.Max(vert);
				vMin.Min(vert);
			}

			// 移動量はトリガー自体に設定するため、回転と拡大のみ乗算。

			CMatrix mRot, mScale, mScaleXRot;
			mRot.MakeRotationFromQuaternion(rot);
			mScale.MakeScaling(scale);
			mScaleXRot = mScale * mRot;


			CVector3 halfExtent = (vMax - vMin) * 0.5f;
			mScaleXRot.Apply(halfExtent);

			CVector3 offset = CVector3::Zero();

			if (halfExtent.y < 0.0f)
			{
				offset.y += halfExtent.y * -1.0f;
			}

			// 負の値がは対応できないため、正に直す。
			for (int i = 0; i < 3; i++)
			{
				halfExtent.m_fVec[i] = fabsf(halfExtent.m_fVec[i]);
			}

			auto res = m_trigger.InitAsBox(halfExtent, position + offset, attribute);

			m_trigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) { OnTriggerEnter(otherData); });
			m_trigger.SetOnTriggerStayFunc(
				[&](CExtendedDataForRigidActor* otherData) { OnTriggerStay(otherData); });
			m_trigger.SetOnTriggerExitFunc(
				[&](CExtendedDataForRigidActor* otherData) { OnTriggerExit(otherData); });

			return res;
		}
	}
}