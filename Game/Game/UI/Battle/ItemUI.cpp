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
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                //オブジェクトネームが"player_kari"と同じだったら
                    if (imgData.EqualObjectName(L"プレイヤーのHPバー") == true)
                    {
                        // UIクラスを作成
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteMPBar->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteMPBar->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの枠
                    if (imgData.EqualObjectName(L"プレイヤーのHPバーの枠") == true)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteFrame->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteFrame->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの下地
                    if (imgData.EqualObjectName(L"プレイヤーのHPの下地") == true)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteBase->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBase->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーのピンチ時のやつ
                    if (imgData.EqualObjectName(L"プレイヤーのHPのピンチ時") == true)
                    {
                        // UIクラスを作成
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteDanger->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteDanger->SetPivot(imgData.pivot);
                        // 非表示にする
                        m_spriteDanger->Deactivate();
                        // フックしたので、trueを返す
                        return true;
                    }


                });
        }

        void CItemUI::OnDestroy()
        {
            DeleteGO(m_spriteMPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
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
            m_spriteMPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}