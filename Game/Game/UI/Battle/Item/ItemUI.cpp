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

        // こいつらは、本実装時にクラスに持たせること
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
                { // ロードするレベル一つ一つにクエリを行う

                // アイテム選択UIの土台部分
                    if ("ItemBase" == imgData.Name)
                    {
                        // UIクラスを作成
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

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 真ん中のアイテムアイコン
                    else if ("Center" == imgData.Name)
                    {
                        // 画像のデータを取得
                        LoadImgData(static_cast<int>(EnItemIcon::enCenter), imgData);

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 右側のアイテムアイコン
                    else if ("Next" == imgData.Name)
                    {
                        // 画像のデータを取得
                        LoadImgData(static_cast<int>(EnItemIcon::enNext), imgData);

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 左側のアイテムアイコン
                    else if ("Back" == imgData.Name)
                    {
                        // 画像のデータを取得
                        LoadImgData(static_cast<int>(EnItemIcon::enBack), imgData);

                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });

            LoadItemIconSprite();
        }

        void CItemUI::LoadImgData(const int itemIconNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // アイテムアイコンの表示位置３種をここで取得
            m_itemIconInitialData[itemIconNum].position = imgData.Position;
            m_itemIconInitialData[itemIconNum].rotateDeg = imgData.RotateDeg;
            m_itemIconInitialData[itemIconNum].scale = imgData.Scale;
            m_itemIconInitialData[itemIconNum].spriteSize = imgData.SpriteSize;
            m_itemIconInitialData[itemIconNum].pivot = imgData.Pivot;
        }

        void CItemUI::LoadItemIconSprite()
        {
            // ここで取得した順にアイテムリストの方も並んでるはず
            // そうじゃないならもう知らん

            // アイテムの名前をアイテムリストから取得
            std::list<std::string> testItemName;
            //nsPlayer::CPlayerManager::GetInstance()->GetItemManager()->GetAllItemName(testItemName);

            testItemName.push_back("Test_1");
            testItemName.push_back("Test_2");
            testItemName.push_back("Test_3");
            testItemName.push_back("Test_4");
            testItemName.push_back("Test_5");

            for (auto forNum : testItemName) {
                // 名前に応じてファイルパスに対応した番号を取得
                const int itemFilePathNum = SearchItemName(forNum);
                int itemIconPos = static_cast<int>(EnItemIcon::enCenter);

                if (0 <= itemFilePathNum) {
                    // UIクラスを作成
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
            // アイテム名で検索
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

            // 毎フレームの処理をここに
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
            // 位置を全部リセット
            for (auto& forNum : m_itemIconSpriteData) {
                forNum.itemIconPos = EnItemIcon::enNotFound;
            }
            // アイコンの位置を加算
            ++m_spriteItemIconNum;
            // 要素数を超えたら０にする
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
            // 位置を全部リセット
            for (auto& forNum : m_itemIconSpriteData) {
                forNum.itemIconPos = EnItemIcon::enNotFound;
            }
            // アイコンの位置を加算
            --m_spriteItemIconNum;
            // 要素数を超えたら０にする
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