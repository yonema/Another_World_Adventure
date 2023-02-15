#include "TutorialEventCut.h"
namespace nsAWA
{
	namespace nsEvent
	{
		const wchar_t* const CTutorialEventCut::m_kText[static_cast<int>(EnTutorialStep::enNum)] =
		{
			L"[���X�e�B�b�N]�ňړ����ł��܂�",
			L"[R2 + ���X�e�B�b�N]�Ń_�b�V�����ł��܂�",
			L"[B]�Ŏ�U���A[Y]�ŋ��U�����ł��܂�",
			L"[A]�ŃX�e�b�v(���)���s���܂�",
			L"[R1 + B]�ŃK�[�h���s���܂�",
			L"[L1 + �e��{�^��]�ŃX�L�����g���܂�",
			L"[Start]�Ń��j���[���J���܂�",
		};

		CTutorialEventCut::CTutorialEventCut()
		{
			m_fontRenderer = NewGO<CFontRenderer>("TutorialEventCutFR");
			SFontParameter param;
			param.anchor = EnAnchors::enTopCenter;
			param.pivot = { 0.5f,0.0f };
			param.position = { 0.0f,50.0f };
			param.text = m_kText[static_cast<int>(m_step)];
			param.color = CVector4::Black();

			m_fontRenderer->Init(param);

			return;
		}

		CTutorialEventCut::~CTutorialEventCut()
		{
			DeleteGO(m_fontRenderer);
			return;
		}

		bool CTutorialEventCut::UpdateEventCut() noexcept
		{
			bool clear = false;

			switch (m_step)
			{
			case EnTutorialStep::enWalk:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			case EnTutorialStep::enRun:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			case EnTutorialStep::enAttack:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			case EnTutorialStep::enStep:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			case EnTutorialStep::enGuard:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			case EnTutorialStep::enSkill:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			case EnTutorialStep::enMenu:
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack))
				{
					ProgressStep();
				}
				break;
			default:
				clear = true;
				break;
			}



			return clear;
		}

		void CTutorialEventCut::ProgressStep()
		{
			if (m_inTransition)
			{
				return;
			}

			m_inTransition = true;

			InvokeFunc([&]()
				{
					int iStep = static_cast<int>(m_step);
					iStep++;
					m_step = static_cast<EnTutorialStep>(iStep);
					if (iStep < static_cast<int>(EnTutorialStep::enNum))
					{
						m_fontRenderer->SetText(m_kText[iStep]);
					}
					m_inTransition = false;
				},
				3.0f
					);


			return;
		}


	}
}