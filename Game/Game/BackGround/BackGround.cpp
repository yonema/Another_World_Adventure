#include "YonemaEnginePreCompile.h"
#include "BackGround.h"

namespace nsAWA {

	namespace nsBackGround {

		const char* const CBackGround::m_kObjName_BackGround = "BackGround";

		bool CBackGround::Start() {

			//地面のモデルを生成。
			m_stageModel = NewGO<CModelRenderer>();

			//メッシュのバッファ情報を初期化。
			nsPhysics::SMeshGeometryBuffer physiceMeshGeomBuffer;

			//地面のモデル情報を初期化。
			SModelInitData stageModelInitData;
			stageModelInitData.modelFilePath = "Assets/Models/samplePlane.fbx";
			stageModelInitData.physicsMeshGeomBuffer = &physiceMeshGeomBuffer;
			stageModelInitData.vertexBias.SetRotation(CVector3::AxisX(), nsMath::YM_PIDIV2);
			m_stageModel->Init(stageModelInitData);

			//当たり判定を初期化。
			m_physicsStaticObject.InitAsMesh(physiceMeshGeomBuffer);

			return true;
		}

		void CBackGround::OnDestroy() {

		}

		void CBackGround::Update(float deltaTime) {


		}
	}
}