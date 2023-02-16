#include "YonemaEnginePreCompile.h"
#include "ItemUI.h"

#include "../../../Player/PlayerManager.h"
#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CItemUI::m_kLevel2DFilePath =
            "Assets/Level2D/Item.tdl";

        const char* CItemUI::m_kItemBaseSpriteFilePath =
            "Assets/Images/ItemRelated/ItemBase.png";

        const char* CItemUI::m_kPotionSpriteFilePath =
            "Assets/Images/ItemRelated/Potion_Temporary.png";

        const char* CItemUI::m_kTestSpriteFilePath[5] =
        {
            "Assets/Images/ItemRelated/Test_1.png",
            "Assets/Images/ItemRelated/Test_2.png",
            "Assets/Images/ItemRelated/Test_3.png",
            "Assets/Images/ItemRelated/Test_4.png",
            "Assets/Images/ItemRelated/Test_5.png"
        };

        // ������́A�{�������ɃN���X�Ɏ������邱��
        enum EnTestItemIcon
        {
            en1,
            en2,
            en3,
            en4,
            en5,
            enMaxTestItemIcon
        };

        const char* m_kTestItemIconFilePath[EnTestItemIcon::enMaxTestItemIcon] =
        {
            "",
            ""
        };

        bool CItemUI::Start()
        {
            return true;
        }

        void CItemUI::LoadLevel()
        {
            
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �A�C�e���I��UI�̓y�䕔��
                    if ("ItemBase" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(
                            m_kItemBaseSpriteFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �^�񒆂̃A�C�e���A�C�R��
                    else if ("Center" == imgData.Name)
                    {
                        // �摜�̃f�[�^���擾
                        LoadImgData(static_cast<int>(EnItemIcon::enCenter), imgData);

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E���̃A�C�e���A�C�R��
                    else if ("Next" == imgData.Name)
                    {
                        // �摜�̃f�[�^���擾
                        LoadImgData(static_cast<int>(EnItemIcon::enNext), imgData);

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �����̃A�C�e���A�C�R��
                    else if ("Back" == imgData.Name)
                    {
                        // �摜�̃f�[�^���擾
                        LoadImgData(static_cast<int>(EnItemIcon::enBack), imgData);

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });

            LoadItemIconSprite();
        }

        void CItemUI::LoadImgData(const int itemIconNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // �A�C�e���A�C�R���̕\���ʒu�R��������Ŏ擾
            m_itemIconInitialData[itemIconNum].position = imgData.Position;
            m_itemIconInitialData[itemIconNum].rotateDeg = imgData.RotateDeg;
            m_itemIconInitialData[itemIconNum].scale = imgData.Scale;
            m_itemIconInitialData[itemIconNum].spriteSize = imgData.SpriteSize;
            m_itemIconInitialData[itemIconNum].pivot = imgData.Pivot;
        }

        void CItemUI::LoadItemIconSprite()
        {
            // �����Ŏ擾�������ɃA�C�e�����X�g�̕�������ł�͂�
            // ��������Ȃ��Ȃ�����m���

            // �A�C�e���̖��O���A�C�e�����X�g����擾
            std::list<std::string> testItemName;
            //nsPlayer::CPlayerManager::GetInstance()->GetItemManager()->GetAllItemName(testItemName);

            testItemName.push_back("Test_1");
            testItemName.push_back("Test_2");
            testItemName.push_back("Test_3");
            testItemName.push_back("Test_4");
            testItemName.push_back("Test_5");

            for (auto forNum : testItemName) {
                // ���O�ɉ����ăt�@�C���p�X�ɑΉ������ԍ����擾
                const int itemFilePathNum = SearchItemName(forNum);
                int itemIconPos = static_cast<int>(EnItemIcon::enCenter);

                if (0 <= itemFilePathNum) {
                    // UI�N���X���쐬
                    m_itemIconSpriteData.emplace_back();
                    m_itemIconSpriteData.back().sprite = NewGO<CSpriteUI>();
                    m_itemIconSpriteData.back().sprite->LoadSprite(
                        m_kTestSpriteFilePath[itemFilePathNum],
                        m_itemIconInitialData[0].spriteSize,
                        static_cast<EnRendererPriority>(m_itemIconInitialData[0].priority),
                        EnAlphaBlendMode::enTrans
                    );
                    m_itemIconSpriteData.back().sprite->LoadInitData(
                        m_itemIconInitialData[0].position,
                        m_itemIconInitialData[0].scale,
                        m_itemIconInitialData[0].pivot
                    );

                    if (static_cast<int>(EnItemIcon::enMaxItemIcon) > itemIconPos) {
                        ++itemIconPos;
                    }
                }
            }
            m_itemIconSpriteData[0].itemIconPos = EnItemIcon::enCenter;
            m_itemIconSpriteData[m_itemIconSpriteData.size() - 1].itemIconPos = EnItemIcon::enBack;
            m_itemIconSpriteData[1].itemIconPos = EnItemIcon::enNext;
        }

        const int CItemUI::SearchItemName(std::string& name)
        {
            // �A�C�e�����Ō���
            if ("Test_1" == name) {
                return EnTestItemIcon::en1;
            }
            else if ("Test_2" == name) {
                return EnTestItemIcon::en2;
            }
            else if ("Test_3" == name) {
                return EnTestItemIcon::en3;
            }
            else if ("Test_4" == name) {
                return EnTestItemIcon::en4;
            }
            else if ("Test_5" == name) {
                return EnTestItemIcon::en5;
            }
            else {
                return -1;
            }

            return -1;
        }

        void CItemUI::OnDestroy()
        {

        }

        void CItemUI::Update(float deltaTime)
        {
            if (false == m_flagDrawSprite) {
                return;
            }

            // ���t���[���̏�����������
            for (auto& forNum : m_itemIconSpriteData) {
                if (EnItemIcon::enNotFound == forNum.itemIconPos) {
                    forNum.sprite->SetDrawingFlag(false);
                }
                else if (EnItemIcon::enCenter == forNum.itemIconPos) {
                    forNum.sprite->SetDrawingFlag(true);
                    forNum.sprite->SetPosition(m_itemIconInitialData[static_cast<int>(EnItemIcon::enCenter)].position);
                }
                else if (EnItemIcon::enBack == forNum.itemIconPos) {
                    forNum.sprite->SetDrawingFlag(true);
                    forNum.sprite->SetPosition(m_itemIconInitialData[static_cast<int>(EnItemIcon::enBack)].position);
                }
                else if (EnItemIcon::enNext == forNum.itemIconPos) {
                    forNum.sprite->SetDrawingFlag(true);
                    forNum.sprite->SetPosition(m_itemIconInitialData[static_cast<int>(EnItemIcon::enNext)].position);
                }
            }
            
            Animation();

        }

        void CItemUI::Animation()
        {

        }

        void CItemUI::MoveNextItemUI()
        {
            // �ʒu��S�����Z�b�g
            for (auto& forNum : m_itemIconSpriteData) {
                forNum.itemIconPos = EnItemIcon::enNotFound;
            }
            // �A�C�R���̈ʒu�����Z
            ++m_spriteItemIconNum;
            // �v�f���𒴂�����O�ɂ���
            if (m_itemIconSpriteData.size() <= m_spriteItemIconNum) {
                m_spriteItemIconNum = 0;
            }

            m_itemIconSpriteData[m_spriteItemIconNum].itemIconPos = EnItemIcon::enCenter;

            if (0 > m_spriteItemIconNum - 1) {
                m_itemIconSpriteData[m_itemIconSpriteData.size() - 1].itemIconPos = EnItemIcon::enBack;
            }
            else {
                m_itemIconSpriteData[m_spriteItemIconNum - static_cast<unsigned __int64>(1)].
                    itemIconPos = EnItemIcon::enBack;
            }

            if (m_itemIconSpriteData.size() <= m_spriteItemIconNum + static_cast<unsigned __int64>(1)) {
                m_itemIconSpriteData[0].itemIconPos = EnItemIcon::enNext;
            }
            else {
                m_itemIconSpriteData[m_spriteItemIconNum + static_cast<unsigned __int64>(1)].
                    itemIconPos = EnItemIcon::enNext;
            }
        }

        void CItemUI::MoveBackItemUI()
        {
            // �ʒu��S�����Z�b�g
            for (auto& forNum : m_itemIconSpriteData) {
                forNum.itemIconPos = EnItemIcon::enNotFound;
            }
            // �A�C�R���̈ʒu�����Z
            --m_spriteItemIconNum;
            // �v�f���𒴂�����O�ɂ���
            if (0 > m_spriteItemIconNum) {
                m_spriteItemIconNum = static_cast<int>(m_itemIconSpriteData.size() - 1);
            }

            m_itemIconSpriteData[m_spriteItemIconNum].itemIconPos = EnItemIcon::enCenter;

            if (0 > m_spriteItemIconNum - 1) {
                m_itemIconSpriteData[m_itemIconSpriteData.size() - 1].itemIconPos = EnItemIcon::enBack;
            }
            else {
                m_itemIconSpriteData[m_spriteItemIconNum - static_cast<unsigned __int64>(1)].
                    itemIconPos = EnItemIcon::enBack;
            }

            if (m_itemIconSpriteData.size() <= m_spriteItemIconNum + static_cast<unsigned __int64>(1)) {
                m_itemIconSpriteData[0].itemIconPos = EnItemIcon::enNext;
            }
            else {
                m_itemIconSpriteData[m_spriteItemIconNum + static_cast<unsigned __int64>(1)].
                    itemIconPos = EnItemIcon::enNext;
            }
        }

        void CItemUI::ActiveDrawing()
        {
            if (nullptr == this || false == IsActive()) {
                return;
            }

            m_spriteBase->SetDrawingFlag(true);
            
            for (auto& forNum : m_itemIconSpriteData) {
                forNum.sprite->SetDrawingFlag(true);
            }

            m_flagDrawSprite = true;
        }

        void CItemUI::DeactiveDrawing()
        {
            if (nullptr == this || false == IsActive()) {
                return;
            }

            m_spriteBase->SetDrawingFlag(false);

            for (auto& forNum : m_itemIconSpriteData) {
                forNum.sprite->SetDrawingFlag(false);
            }

            m_flagDrawSprite = false;
        }

        void CItemUI::ActivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteBase->Activate();

            for (auto& forNum : m_itemIconSpriteData) {
                forNum.sprite->Activate();
            }
        }

        void CItemUI::DeactivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteBase->SetDrawingFlag(false);
            m_spriteBase->Deactivate();

            for (auto& forNum : m_itemIconSpriteData) {
                forNum.sprite->SetDrawingFlag(false);
                forNum.sprite->Deactivate();
            }
        }
    }
}