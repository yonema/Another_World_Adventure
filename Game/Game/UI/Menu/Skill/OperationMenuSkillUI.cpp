#include "YonemaEnginePreCompile.h"
#include "OperationMenuSkillUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool COperationMenuSkillUI::Start()
        {
            // スキルの情報を取得

            return true;
        }

        void COperationMenuSkillUI::OnDestroy()
        {

        }

        void COperationMenuSkillUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに
            switch (m_windowStatus) {
            case EnWindowStatus::enActiveOrPassive:
                OperationActiveOrPassive();
                break;
            case EnWindowStatus::enNowSetSkill:
                OperationNowSetSkill();
                break;
            case EnWindowStatus::enSelectionSetSkill:
                OperationSelectionSetSkill();
                break;
            default:

                break;
            }
        }

        void COperationMenuSkillUI::Animation()
        {

        }

        ////////////////////////////////////////////////////////////
        // Load
        ////////////////////////////////////////////////////////////

        void COperationMenuSkillUI::LoadNowSetSkill()
        {
            // ここで、現在セットしてるスキルの情報を取得
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {

            }
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {

            }

        }

        void COperationMenuSkillUI::LoadSelectionSetSkill()
        {
            // ここで、現在持っているスキルすべての情報を取得

        }

        ////////////////////////////////////////////////////////////
        // Operation
        ////////////////////////////////////////////////////////////

        void COperationMenuSkillUI::OperationActiveOrPassive()
        {
            // 決定
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                // ここで、スキルの情報の読み込みをおこなう
                LoadNowSetSkill();
                LoadSelectionSetSkill();

                m_windowStatus = EnWindowStatus::enNowSetSkill;
            }
            // キャンセル
            if (true == Input()->IsTrigger(EnActionMapping::enCancel)) {
                m_flagEndProcessing = true;
            }

            // 左
            if (0.0f > Input()->GetVirtualAxis(EnAxisMapping::enRight)) {
                m_activeOrPassive = EnActiveOrPassive::enActive;
            }
            // 右
            if (0.0f < Input()->GetVirtualAxis(EnAxisMapping::enRight)) {
                m_activeOrPassive = EnActiveOrPassive::enPassive;
            }
        }

        void COperationMenuSkillUI::OperationNowSetSkill()
        {
            // 決定
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                m_windowStatus = EnWindowStatus::enSelectionSetSkill;
            }
            // キャンセル
            if (true == Input()->IsTrigger(EnActionMapping::enCancel)) {
                m_windowStatus = EnWindowStatus::enActiveOrPassive;
            }

            // 上
            if (0.0f < Input()->GetVirtualAxis(EnAxisMapping::enForward)) {
                if (EnNowSetSkillFrame::en1_A >= m_nowSetSkillFrame) {
                    m_nowSetSkillFrame = EnNowSetSkillFrame::en1_A;
                }
                else {
                    m_nowSetSkillFrame =
                        static_cast<EnNowSetSkillFrame>(static_cast<int>(m_nowSetSkillFrame) - 1);
                }
            }
            // 下
            if (0.0f > Input()->GetVirtualAxis(EnAxisMapping::enForward)) {
                if (EnNowSetSkillFrame::en6_RT <= m_nowSetSkillFrame) {
                    m_nowSetSkillFrame = EnNowSetSkillFrame::en6_RT;
                }
                else {
                    m_nowSetSkillFrame =
                        static_cast<EnNowSetSkillFrame>(static_cast<int>(m_nowSetSkillFrame) + 1);
                }
            }
        }

        void COperationMenuSkillUI::OperationSelectionSetSkill()
        {
            // 決定
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                // スキルを付け替える
                ChangeSetSkill();
                m_windowStatus = EnWindowStatus::enNowSetSkill;
            }
            // キャンセル
            if (true == Input()->IsTrigger(EnActionMapping::enCancel)) {
                m_windowStatus = EnWindowStatus::enNowSetSkill;
            }

            // 上
            if (0.0f < Input()->GetVirtualAxis(EnAxisMapping::enForward)) {
                if (0 >= m_cursorPositionSelectionSetSkill) {
                    m_cursorPositionSelectionSetSkill = 0;
                }
                else {
                    --m_cursorPositionSelectionSetSkill;
                }
            }
            // 下
            if (0.0f > Input()->GetVirtualAxis(EnAxisMapping::enForward)) {
                if (m_selectionSetSkill.size() <= m_cursorPositionSelectionSetSkill) {
                    m_cursorPositionSelectionSetSkill = m_selectionSetSkill.size();
                }
                else {
                    ++m_cursorPositionSelectionSetSkill;
                }
            }
        }

        void COperationMenuSkillUI::ChangeSetSkill()
        {
            // m_nowSetSkillFrameのところに、
            // 選択したスキルを入れ替える
            

        }
    }
}