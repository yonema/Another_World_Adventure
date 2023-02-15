#include "YonemaEnginePreCompile.h"
#include "GuildQuestText.h"
#include "../../../Player/Player.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CGuildQuestText::Start()
        {
            //�N�G�X�g������B���x���擾 ����܂�Find�������Ȃ���������...
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

            if (m_questProgress == EnQuestProgress::enNotReceive) //�󒍂��Ă��Ȃ�
            {
                m_fontRenderer->SetColor(CVector4::White());
            }
            else if (m_questProgress == EnQuestProgress::enReceive) //�󒍂��Ă��邪�B�����Ă��Ȃ�
            {
                m_fontRenderer->SetColor(CVector4::Gray());
            }
            else //�B�����Ă���
            {
                m_fontRenderer->SetColor(CVector4::Red());
            }
        }

        void CGuildQuestText::Select()
        {
            if (m_questProgress == EnQuestProgress::enNotReceive) //�󒍂��Ă��Ȃ�
            {
                //�󒍂��Ă��Ȃ��̂Ŏ󒍁B

                //�󒍎����������s
                if (m_onReceiveEvent != nullptr)
                {
                    m_onReceiveEvent();
                }
               

                m_questProgress = EnQuestProgress::enReceive;
            }
            else if (m_questProgress == EnQuestProgress::enReceive) //�󒍂��Ă��邪�B�����Ă��Ȃ�
            {
                //�󒍂��Ă��邪�N���A���Ă��Ȃ��̂ŉ������Ȃ��B
            }
            else //�B�����Ă���
            {
                //�B�����Ă���Ȃ�B�������������s
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