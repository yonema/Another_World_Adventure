#include "YonemaEnginePreCompile.h"
#include "BackGround.h"

namespace nsAWA {

	namespace nsBackGround {

		const char* const CBackGround::m_kObjName_BackGround = "BackGround";

		bool CBackGround::Start() {

			//�n�ʂ̃��f���𐶐��B
			m_stageModel = NewGO<CModelRenderer>();

			//���b�V���̃o�b�t�@�����������B
			nsPhysics::SMeshGeometryBuffer physiceMeshGeomBuffer;

			//�n�ʂ̃��f�������������B
			SModelInitData stageModelInitData;
			stageModelInitData.modelFilePath = "Assets/Models/samplePlane.fbx";
			stageModelInitData.physicsMeshGeomBuffer = &physiceMeshGeomBuffer;
			stageModelInitData.vertexBias.SetRotation(CVector3::AxisX(), nsMath::YM_PIDIV2);
			m_stageModel->Init(stageModelInitData);

			//�����蔻����������B
			m_physicsStaticObject.InitAsMesh(physiceMeshGeomBuffer);

			return true;
		}

		void CBackGround::OnDestroy() {

		}

		void CBackGround::Update(float deltaTime) {


		}
	}
}