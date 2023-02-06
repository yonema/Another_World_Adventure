#include "YonemaEnginePreCompile.h"
#include "ItemUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CItemUI::Start()
        {
            return true;
        }

        void CItemUI::LoadLevel(const char* tdlFilePath)
        {
            /*
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                //オブジェクトネームが"player_kari"と同じだったら
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteMPBar->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteMPBar->SetPivot(imgData.Pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの枠
                    else if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteFrame->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteFrame->SetPivot(imgData.Pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの下地
                    else if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteBase->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBase->SetPivot(imgData.Pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーのピンチ時のやつ
                    else if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteDanger->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteDanger->SetPivot(imgData.Pivot);
                        // 非表示にする
                        m_spriteDanger->Deactivate();
                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });
                */
        }

        void CItemUI::OnDestroy()
        {
            //DeleteGO(m_spriteMPBar);
            //DeleteGO(m_spriteFrame);
            //DeleteGO(m_spriteBase);
            //DeleteGO(m_spriteDanger);
        }

        void CItemUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // MPバーのアニメーション
            Animation();

        }

        void CItemUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            //m_spriteMPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}