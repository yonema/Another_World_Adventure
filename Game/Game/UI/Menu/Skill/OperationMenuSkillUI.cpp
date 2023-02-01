#include "YonemaEnginePreCompile.h"
#include "OperationMenuSkillUI.h"

#include "../../../Skill/SkillManager.h"
#include "../../../CSV/CSVManager.h"
#include "../../../Player/Player.h"

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

        void COperationMenuSkillUI::LoadSkillData()
        {
            // ここで、現在セットしてるスキルを取得
            // プレイヤーを検索
            auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
            if (player == nullptr) {
                nsGameWindow::MessageBoxWarning(L"COperationMenuSkillUI : player が見つかりませんでした。");
            }
            // アクティブ
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                // 要素数を決定
                m_nowSetSkill.resize(m_kActiveSkillMaxNum);
                // 名前を代入
                for (int skillNum = 0; m_kActiveSkillMaxNum > skillNum; ++skillNum) {
                    m_nowSetSkill[skillNum] = player->GetActiveSkillName(skillNum);
                }
            }
            // パッシブ
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {
                // 要素数を決定
                m_nowSetSkill.resize(m_kPassiveSkillMaxNum);
                // 名前を代入
                for (int skillNum = 0; m_kPassiveSkillMaxNum > skillNum; ++skillNum) {
                    m_nowSetSkill[skillNum] = player->GetActiveSkillName(skillNum);
                }
            }

            // ここで、所持してるスキル全部を取得
            // アクティブ
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                nsCSV::CCsvManager csvManager;
                csvManager.LoadCSV(L"Assets/CSV/Player/ActiveSkillList.csv");
                std::list<std::vector<std::string>> csvData;
                csvData = csvManager.GetCsvData();

                for (auto& forData : csvData) {
                    m_selectionSetSkill.push_back(forData[0]);
                }
            }
            // パッシブ
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {
                nsCSV::CCsvManager csvManager;
                csvManager.LoadCSV(L"Assets/CSV/Player/PassiveSkillList.csv");
                std::list<std::vector<std::string>> csvData;
                csvData = csvManager.GetCsvData();

                for (auto& forData : csvData) {
                    m_selectionSetSkill.push_back(forData[0]);
                }
            }
        }



        ////////////////////////////////////////////////////////////
        // Operation
        ////////////////////////////////////////////////////////////

        void COperationMenuSkillUI::OperationActiveOrPassive()
        {
            // 決定
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                // ここで、スキルの情報の読み込みをおこなう
                LoadSkillData();

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

            // 選択したスキル欄のところのスキルを入れ替える
            nsSkill::CSkillManager skillManager;
            skillManager.SetActiveSkill(
                static_cast<int>(m_nowSetSkillFrame), m_selectionSetSkill[m_cursorPositionSelectionSetSkill]
            );
        }
    }
}