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
            m_testFontActiveOrPassive->LoadFont(L"�A�N�e�B�u");

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
            // ���t���[���̏�����������
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
                m_testFontActiveOrPassive->SetText(L"�A�N�e�B�u");
            }
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {
                m_testFontActiveOrPassive->SetText(L"�p�b�V�u");
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
            // �����ŁA���݃Z�b�g���Ă�X�L�����擾
            // �v���C���[������
            if (false == nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {
                nsGameWindow::MessageBoxWarning(L"COperationMenuSkillUI : player ��������܂���ł����B");
            }
            // �A�N�e�B�u
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                // �v�f��������
                m_nowSetSkillName.resize(m_kActiveSkillMaxNum);
                // ���O����
                for (int skillNum = 0; m_kActiveSkillMaxNum > skillNum; ++skillNum) {
                    m_nowSetSkillName[skillNum] = nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(skillNum);
                }
            }
            // �p�b�V�u
            else if (EnActiveOrPassive::enPassive == m_activeOrPassive) {
                // �v�f��������
                m_nowSetSkillName.resize(m_kPassiveSkillMaxNum);
                // ���O����
                for (int skillNum = 0; m_kPassiveSkillMaxNum > skillNum; ++skillNum) {
                    m_nowSetSkillName[skillNum] = nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(skillNum);
                }
            }

            // �����ŁA�������Ă�X�L���S�����擾
            m_fontSelectionSetSkillName = NewGO<CFontArrayUI>();
            // �A�N�e�B�u
            if (EnActiveOrPassive::enActive == m_activeOrPassive) {
                //m_selectionSetSkillData = playerManager.GetCanUseActiveSkillList();

                //for (auto forSkillData : m_selectionSetSkillData) {
                //    m_fontSelectionSetSkillName->NewLoadFont(
                //        nsUtils::GetWideStringFromString(forSkillData.name).c_str()
                //    );
                //}
            }
            // �p�b�V�u
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
            // ����
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                // �����ŁA�X�L���̏��̓ǂݍ��݂������Ȃ�
                LoadSkillData();

                m_windowStatus = EnWindowStatus::enNowSetSkill;
            }
            // �L�����Z��
            if (true == Input()->IsTrigger(EnActionMapping::enCancel)) {
                m_flagEndProcessing = true;
            }
            
            // ��
            if (0.0f > Input()->GetVirtualAxis(EnAxisMapping::enRight)) {
                m_activeOrPassive = EnActiveOrPassive::enActive;
            }
            // �E
            if (0.0f < Input()->GetVirtualAxis(EnAxisMapping::enRight)) {
                m_activeOrPassive = EnActiveOrPassive::enPassive;
            }
        }

        void COperationMenuSkillUI::OperationNowSetSkill()
        {
            // ����
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                m_windowStatus = EnWindowStatus::enSelectionSetSkill;
            }
            // �L�����Z��
            if (true == Input()->IsTrigger(EnActionMapping::enCancel)) {
                m_windowStatus = EnWindowStatus::enActiveOrPassive;
            }

            // ��
            if (0.0f < Input()->GetVirtualAxis(EnAxisMapping::enForward)) {
                if (EnNowSetSkillFrame::en1_A >= m_nowSetSkillFrame) {
                    m_nowSetSkillFrame = EnNowSetSkillFrame::en1_A;
                }
                else {
                    m_nowSetSkillFrame =
                        static_cast<EnNowSetSkillFrame>(static_cast<int>(m_nowSetSkillFrame) - 1);
                }
            }
            // ��
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
            // ����
            if (true == Input()->IsTrigger(EnActionMapping::enDecision)) {
                // �X�L����t���ւ���
                ChangeSetSkill();
                m_windowStatus = EnWindowStatus::enNowSetSkill;
            }
            // �L�����Z��
            if (true == Input()->IsTrigger(EnActionMapping::enCancel)) {
                m_windowStatus = EnWindowStatus::enNowSetSkill;
            }

            // ��
            if (0.0f < Input()->GetVirtualAxis(EnAxisMapping::enForward)) {
                if (0 >= m_cursorPositionSelectionSetSkill) {
                    m_cursorPositionSelectionSetSkill = 0;
                }
                else {
                    --m_cursorPositionSelectionSetSkill;
                }
            }
            // ��
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
            // m_nowSetSkillFrame�̂Ƃ���ɁA
            // �I�������X�L�������ւ���

            // �I�������X�L�����̂Ƃ���̃X�L�������ւ���
            if (false == nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {
                nsGameWindow::MessageBoxWarning(L"COperationMenuSkillUI : player ��������܂���ł����B");
            }
            // list�̃C�e���[�^�[��I�����Ă�Ƃ���܂ňړ�����
            //std::list<nsSkill::SActiveSkillData>::iterator setSkillData = m_selectionSetSkillData.begin();
            //for (int forNum = 0; forNum < m_cursorPositionSelectionSetSkill; ++forNum) {
            //    ++setSkillData;
            //}
            //
            //// �X�L�����Z�b�g
            //nsPlayer::CPlayerManager::GetInstance()->SetActiveSkill(
            //    static_cast<int>(m_nowSetSkillFrame), setSkillData->name
            //);
        }
    }
}