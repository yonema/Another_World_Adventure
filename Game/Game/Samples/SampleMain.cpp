#include "SampleMain.h"
#include "ModelRendererSample.h"
#include "SkeltalAnimationSample.h"
#include "AnimationEventSample.h"
#include "GetBoneMatrixSample.h"
#include "LoadAsynchronousSample.h"
#include "SpriteSample.h"
#include "FontSample.h"
#include "EffectSample.h"
#include "SoundSample.h"
#include "NavMeshSample.h"
#include "PhysicsSample.h"
#include "TriggerSample.h"
#include "CharacterControllerSample.h"

namespace nsAWA
{
	namespace nsSamples
	{
		namespace
		{
			enum class EnSampleIdx
			{
				enModelRenderer,
				enSkeltalAnimation,
				enAnimationEvent,
				enGetBoneMatrix,
				enLoadAsynchronous,
				enSprite,
				enFont,
				enEffect,
				enSound,
				enNavMesh,
				enPhysics,
				enTrigger,
				enCharacterController,
			};

			constexpr EnSampleIdx g_kSampleIdx = EnSampleIdx::enLoadAsynchronous;
		}

		bool CSampleMain::Start()
		{
			switch (g_kSampleIdx)
			{
			case EnSampleIdx::enModelRenderer:
				m_sampleGO = NewGO<CModelRendererSample>("ModelRendererSample");
				break;
			case EnSampleIdx::enSkeltalAnimation:
				m_sampleGO = NewGO<CSkeltalAnimationSample>("SkeltalAnimationSample");
				break;
			case EnSampleIdx::enAnimationEvent:
				m_sampleGO = NewGO<CAnimationEventSample>("AnimationEventSample");
				break;
			case EnSampleIdx::enGetBoneMatrix:
				m_sampleGO = NewGO<CGetBoneMatrixSample>("GetBoneMatrixSample");
				break;
			case EnSampleIdx::enLoadAsynchronous:
				m_sampleGO = NewGO<CLoadAsynchronousSample>("LoadAsynchronousSample");
				break;
			case EnSampleIdx::enSprite:
				m_sampleGO = NewGO<CSpriteSample>("SpriteSample");
				break;
			case EnSampleIdx::enFont:
				m_sampleGO = NewGO<CFontSample>("FontSample");
				break;
			case EnSampleIdx::enEffect:
				m_sampleGO = NewGO<CEffectSample>("EffectSample");
				break;
			case EnSampleIdx::enSound:
				m_sampleGO = NewGO<CSoundSample>("SoundSample");
				break;
			case EnSampleIdx::enNavMesh:
				m_sampleGO = NewGO<CNavMeshSample>("NavMeshSample");
				break;
			case EnSampleIdx::enPhysics:
				m_sampleGO = NewGO<CPhysicsSample>("PhysicsSample");
				break;
			case EnSampleIdx::enTrigger:
				m_sampleGO = NewGO<CTriggerSample>("TriggerSample");
				break;
			case EnSampleIdx::enCharacterController:
				m_sampleGO = NewGO<CCharacterControllerSample>("CharacterControllerSample");
				break;
			default:
				m_sampleGO = NewGO<CModelRendererSample>("ModelRendererSample");
				break;
			}

			return true;
		}

		void CSampleMain::OnDestroy()
		{
			DeleteGO(m_sampleGO);

			return;
		}

		void CSampleMain::Update(float deltaTime)
		{
			if (Keyboard()->IsTrigger(EnKeyButton::enEscape))
			{
				DeleteGO(this);
				ExitGame();
			}
			return;
		}
	}
}