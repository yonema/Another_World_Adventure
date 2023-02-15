#include "YonemaEnginePreCompile.h"
#include "GuildQuestText.h"
#include "../../../Player/Player.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CGuildQuestText::Start()
        {
            //クエスト名から達成度を取得 あんまりFindしたくなかったけど...
            nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

            if (player != nullptr)
            {

                bool isReceived = player->IsQuestReceived(m_questName);
                if (isReceived == true)
                {
                    bool isCompleted = player->IsQuestCompleted(m_questName);

                    if (isCompleted == true)
                    {
                        m_questProgress = EnQuestProgress::enComplete;
                    }
                    else
                    {
                        m_questProgress = EnQuestProgress::enReceive;
                    }
                }
                else
                {
                    m_questProgress = EnQuestProgress::enNotReceive;
                }
            }

            m_fontRenderer = NewGO<CFontRenderer>();
            SFontParameter initParam;
            m_fontRenderer->Init(initParam);

            std::wstring wQuestName = nsUtils::GetWideStringFromString(m_questName);
            m_fontRenderer->SetText(wQuestName.c_str());
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