#include "YonemaEnginePreCompile.h"
#include "GuildWindowUI.h"

#include "../../SpriteUI.h"
#include "GuildQuestText.h"
#include "../../../Player/Player.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CGuildWindowUI::Start()
        {
            m_level.Load(m_kGuildWindowFilePath);

            m_level.RegisterAnimationEvent("InnAppear", "Appeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
                {
                    //Quest Appear
                    
                    m_cursorRenderer = NewGO<CSpriteRenderer>();
                    SSpriteInitData initData;
                    initData.filePath = "Assets/Images/Institution/Guild/Arrow.png";
                    initData.alphaBlendMode = EnAlphaBlendMode::enTrans;
                    initData.spriteSize = CVector2(48.0f,48.0f);

                    m_cursorRenderer->Init(initData);

                    m_cursorRenderer->SetPosition(m_kCursorStandardPosition);
                    InitQuests();

                    m_playingAnimation = false;
                }
            );

            m_level.RegisterAnimationEvent("InnDisappear", "Disappeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
                {
                    m_endFlag = true;
                }
            );


            m_playingAnimation = true;
            m_level.PlayAnimation("InnAppear");

            return true;
        }
        void CGuildWindowUI::OnDestroy()
        {
            m_level.Clear();
        }

        void CGuildWindowUI::Update(float deltaTime)
        {
            if (m_playingAnimation == true || m_isInputDisable == true)
            {
                m_disableTime += deltaTime;

                if (m_disableTime >= m_kWaitTime)
                {
                    m_disableTime = 0.0f;
                    m_isInputDisable = false;
                }

                return;
            }

            if (Input()->GetVirtualAxis(EnAxisMapping::enForward) >= 0.8f)
            {
                SelectUp();

                return;
            }
            else if(Input()->GetVirtualAxis(EnAxisMapping::enForward) <= -0.8f)
            {
                SelectDown();
                return;
            }

            if (Input()->IsTrigger(EnActionMapping::enDecision))
            {
                SelectOK();
                return;
            }

            if (Input()->IsTrigger(EnActionMapping::enCancel))
            {
                m_playingAnimation = true;

                for (CGuildQuestText* quest : m_showQuests)
                {
                    DeleteGO(quest);
                }

                DeleteGO(m_cursorRenderer);

                m_level.PlayAnimation("InnDisappear");
                return;
            }
        }

        void CGuildWindowUI::InitQuests()
        {
            //�ǂ������猻�݂̈˗����X�g������Ă���K�v������?


            auto* questText1 = NewGO<CGuildQuestText>(EnGOPriority::enMax);
            questText1->SetQuestName("�M��������! 1��");
            questText1->SetEventOnReceive([]()
                {
                    nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

                    if (player != nullptr)
                    {
                        player->SetSlayQuest("�M��������! 1��","Giyara",1);
                    }
                }
            );

            questText1->SetEventOnClear([]() 
                {
                    //�˗��N���A���̏���
                });

            m_showQuests.emplace_back(questText1);
            auto* questText2 = NewGO<CGuildQuestText>(EnGOPriority::enMax);
            questText2->SetQuestName("�X�P���g������! 3��");
            m_showQuests.emplace_back(questText2);
            questText2->SetEventOnReceive([]()
                {
                    nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

                    if (player != nullptr)
                    {
                        player->SetSlayQuest("�X�P���g������! 3��", "Skeleton", 3);
                    }
                }
            );

            questText2->SetEventOnClear([]()
                {
                    //�˗��N���A���̏���
                });

            int count = 0;
            for (CGuildQuestText* quest : m_showQuests)
            {
                CVector2 position = CVector2(m_kTextStandardPosition.x, m_kTextStandardPosition.y + m_kOffset * count);
                
                quest->SetPosition(position);

                count++;
            }
        }

        void CGuildWindowUI::SelectUp()
        {
            m_selectingIndex--;

            if (m_selectingIndex < 0)
            {
                m_selectingIndex = static_cast<int>(m_showQuests.size()) - 1;
            }

            CVector2 position = CVector2(m_kCursorStandardPosition.x, m_kCursorStandardPosition.y + m_kOffset * m_selectingIndex);

            m_cursorRenderer->SetPosition(position);

            m_isInputDisable = true;
        }

        void CGuildWindowUI::SelectDown()
        {
            m_selectingIndex++;

            if (m_selectingIndex >= static_cast<int>(m_showQuests.size()))
            {
                m_selectingIndex = 0;
            }

            CVector2 position = CVector2(m_kCursorStandardPosition.x, m_kCursorStandardPosition.y + m_kOffset * m_selectingIndex);

            m_cursorRenderer->SetPosition(position);

            m_isInputDisable = true;
        }
        
        void CGuildWindowUI::SelectOK()
        {
            m_showQuests[m_selectingIndex]->Select();
        }
    }
}