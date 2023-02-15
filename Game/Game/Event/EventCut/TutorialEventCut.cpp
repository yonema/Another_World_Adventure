#include "TutorialEventCut.h"
namespace nsAWA
{
	namespace nsEvent
	{
		const wchar_t* const CTutorialEventCut::m_kText[static_cast<int>(EnTutorialStep::enNum)] =
		{
			L"[左スティック]で移動ができます",
			L"[R2 + 左スティック]でダッシュができます",
			L"[B]で弱攻撃、[Y]で強攻撃ができます",
			L"[A]でステップ(回避)が行えます",
			L"[R1 + B]でガードが行えます",
			L"[L1 + 各種ボタン]でスキルを使えます",
			L"[Start]でメニューが開けます",
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