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
			// �R���W�������f���𐶐�����

			nsPhysics::SMeshGeometryBuffer physiceMeshGeomBuffer;

			SModelInitData modelInitData;
			modelInitData.modelFilePath = collisionModelFilePath;
			modelInitData.physicsMeshGeomBuffer = &physiceMeshGeomBuffer;

			auto* mr = NewGO<CModelRenderer>();
			// ��u����Ƃ��\�������Ȃ�
			mr->SetScale(0.0f);
			mr->Init(modelInitData);
			// ���f���͕K�v�Ȃ����炷���ɔj��
			DeleteGO(mr);


			// �R���W�������f������ŏ����W�A�ő���W�����߂�B

			CVector3 vMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			CVector3 vMin(FLT_MAX, FLT_MAX, FLT_MAX);

			for (const auto& vert : physiceMeshGeomBuffer.m_vertices)
			{
				vMax.Max(vert);
				vMin.Min(vert);
			}

			// �ړ��ʂ̓g���K�[���̂ɐݒ肷�邽�߁A��]�Ɗg��̂ݏ�Z�B

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

			// ���̒l���͑Ή��ł��Ȃ����߁A���ɒ����B
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