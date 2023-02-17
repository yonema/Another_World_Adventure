#include "HumanModelRenderer.h"
#include "HumanManager.h"

namespace nsAWA
{
	namespace nsHumans
	{
		const float CHumanModelRenderer::m_kModelScale = 0.1f;
		const float CHumanModelRenderer::m_kVertexBiasXDegAngle = 90.0f;
		const float CHumanModelRenderer::m_kDistanceToReducingUpdate = 100.0f;


		bool CHumanModelRenderer::Start()
		{

			return true;
		}

		void CHumanModelRenderer::Update(float deltaTime)
		{
			CheckLoading();

			return;
		}

		void CHumanModelRenderer::OnDestroy()
		{
			Release();

			return;
		}



		void CHumanModelRenderer::Init(
			const char* name,
			const CVector3& position,
			const CQuaternion& rotation,
			const char* filePath,
			bool isShadowReceiver
		)
		{
			Release();

			SModelInitData modelInitData;

			modelInitData.modelFilePath = filePath;
			modelInitData.animInitData.Init(
				static_cast<int>(EnHumanAnimType::enNum),
				g_kAnimFilePaths
			);
			modelInitData.vertexBias.SetRotationXDeg(m_kVertexBiasXDegAngle);
			modelInitData.retargetSkeltonName = CHumanManager::m_kRetargetSkeltonName;
			modelInitData.distanceToReducingUpdate = m_kDistanceToReducingUpdate;

			modelInitData.SetFlags(EnModelInitDataFlags::enLoadingAsynchronous);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterAnimationBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterTextureBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enCullingOff);
			modelInitData.SetFlags(EnModelInitDataFlags::enShadowCaster);
			if (isShadowReceiver != true)
			{
				modelInitData.SetFlags(EnModelInitDataFlags::enShadowReceiver, false);
			}

			m_modelRenderer = NewGO<CModelRenderer>();
			m_modelRenderer->SetPosition(position);
			m_modelRenderer->SetScale(m_kModelScale);
			m_modelRenderer->SetRotation(rotation);

			m_modelRenderer->Init(modelInitData);

			m_loadingState = EnLoadingState::enNowLoading;


			return;
		}

		void CHumanModelRenderer::Release()
		{
			DeleteGO(m_modelRenderer);
			m_modelRenderer = nullptr;

			m_loadingState = EnLoadingState::enBeforeLoading;

			return;
		}

		void CHumanModelRenderer::CheckLoading()
		{
			if (m_loadingState != EnLoadingState::enNowLoading || IsValid() != true)
			{
				return;
			}

			if (m_modelRenderer->IsLoadingAsynchronous() != true)
			{
				m_loadingState = EnLoadingState::enAfterLoading;
			}

			return;
		}



	}
}