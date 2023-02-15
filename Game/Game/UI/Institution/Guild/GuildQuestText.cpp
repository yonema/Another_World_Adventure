#include "YonemaEnginePreCompile.h"
#include "GuildQuestText.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CGuildQuestText::Start()
        {
            m_fontRenderer = NewGO<CFontRenderer>();
            SFontParameter initParam;
            m_fontRenderer->Init(initParam);

            m_fontRenderer->SetText(m_questName.c_str());
            m_fontRenderer->SetPivot(m_kTextPivot);

            return true;
        }

        void CGuildQuestText::Update(float deltaTime)
        {
            m_fontRenderer->SetPosition(m_fontPosition);

            if (m_questProgress == EnQuestProgress::enNotReceive) //受注していない
            {
                m_fontRenderer->SetColor(CVector4::White());
            }
            else if (m_questProgress == EnQuestProgress::enReceive) //受注しているが達成していない
            {
                m_fontRenderer->SetColor(CVector4::Gray());
            }
            else //達成している
            {
                m_fontRenderer->SetColor(CVector4::Red());
            }
        }

        void CGuildQuestText::Select()
        {
            if (m_questProgress == EnQuestProgress::enNotReceive) //受注していない
            {
                //受注していないので受注。

                //受注時処理を実行
                if (m_onReceiveEvent != nullptr)
                {
                    m_onReceiveEvent();
                }
               

                m_questProgress = EnQuestProgress::enReceive;
            }
            else if (m_questProgress == EnQuestProgress::enReceive) //受注しているが達成していない
            {
                //受注しているがクリアしていないので何もしない。
            }
            else //達成している
            {
                //達成しているなら達成時処理を実行
                if (m_onClearEvent != nullptr)
                {
                    m_onClearEvent();
                }

                m_questProgress = EnQuestProgress::enNotReceive;
            }
        }

        void CGuildQuestText::OnDestroy()
        {
            DeleteGO(m_fontRenderer);
        }

        void CGuildQuestText::SetEventOnReceive(std::function<void(void)> eventFunc)
        {
            m_onReceiveEvent = eventFunc;
        }

        void CGuildQuestText::SetEventOnClear(std::function<void(void)> eventFunc)
        {
            m_onClearEvent = eventFunc;
        }
    }
}