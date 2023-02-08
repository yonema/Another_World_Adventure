#include "YonemaEnginePreCompile.h"
#include "OperationMenuSkillUI.h"

#include "../../../Player/PlayerManager.h"
#include "../../../CSV/CSVManager.h"
#include "../../../Player/Player.h"
#include "../../FontArrayUI.h"
#include "../../FontUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool COperationMenuSkillUI::Start()
        {
            m_testFontActiveOrPassive = NewGO<CFontUI>();
            m_testFontActiveOrPassive->LoadFont(L"アクティブ");

            m_testFontNowSetSkillName = NewGO<CFontArrayUI>();

            return true;
        }

        void COperationMenuSkillUI::OnDestroy()
        {
            DeleteGO(m_testFontActiveOrPassive);
            DeleteGO(m_testFontNowSetSkillName);
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

            TestFont();
        }

        void COperationMenuSkillUI::TestFont()
        {
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                m_testFontActiveOrPassive->SetText(L"アクティブ");
            }
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {
                m_testFontActiveOrPassive->SetText(L"パッシブ");
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
            if (false == nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {
                nsGameWindow::MessageBoxWarning(L"COperationMenuSkillUI : player が見つかりませんでした。");
            }
            // アクティブ
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                // 要素数を決定
                m_nowSetSkillName.resize(m_kActiveSkillMaxNum);
                // 名前を代入
                for (int skillNum = 0; m_kActiveSkillMaxNum > skillNum; ++skillNum) {
                    m_nowSetSkillName[skillNum] = nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(skillNum);
                }
            }
            // パッシブ
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {
                // 要素数を決定
                m_nowSetSkillName.resize(m_kPassiveSkillMaxNum);
                // 名前を代入
                for (int skillNum = 0; m_kPassiveSkillMaxNum > skillNum; ++skillNum) {
                    m_nowSetSkillName[skillNum] = nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(skillNum);
                }
            }

            // ここで、所持してるスキル全部を取得
            m_fontSelectionSetSkillName = NewGO<CFontArrayUI>();
            // アクティブ
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                //m_selectionSetSkillData = playerManager.GetCanUseActiveSkillList();

                //for (auto forSkillData : m_selectionSetSkillData) {
                //    m_fontSelectionSetSkillName->NewLoadFont(
                //        nsUtils::GetWideStringFromString(forSkillData.name).c_str()
                //    );
                //}
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

            for (int forNum = 0; m_nowSetSkillName.size() > forNum; ++forNum) {

            }
            for (auto forName : m_nowSetSkillName) {
                m_testFontNowSetSkillName->NewLoadFont(nsUtils::GetWideStringFromString(forName).c_str());
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
                    //m_cursorPositionSelectionSetSkill = static_cast<int>(m_selectionSetSkillData.size());
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
            if (false == nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {
                nsGameWindow::MessageBoxWarning(L"COperationMenuSkillUI : player が見つかりませんでした。");
            }
            // listのイテレーターを選択してるところまで移動する
            //std::list<nsSkill::SActiveSkillData>::iterator setSkillData = m_selectionSetSkillData.begin();
            //for (int forNum = 0; forNum < m_cursorPositionSelectionSetSkill; ++forNum) {
            //    ++setSkillData;
            //}
            //
            //// スキルをセット
            //nsPlayer::CPlayerManager::GetInstance()->SetActiveSkill(
            //    static_cast<int>(m_nowSetSkillFrame), setSkillData->name
            //);
        }
    }
}