#pragma once
#include "../../YonemaEngine/Graphics/Fonts/FontRenderer.h"

namespace nsAWA
{
    namespace nsUI
    {
        class CFontArrayUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CFontArrayUI() = default;
            ~CFontArrayUI() = default;


        public:
            // フォントデータの作成
            void NewLoadFont(const wchar_t* text, EnFontType fontType = static_cast<EnFontType>(0));


        public: // Set function
            void SetText(const int fontNum, const wchar_t* text)
            {
                m_fontRenderers[fontNum]->SetText(text);
            }

            void SetPosition(const int fontNum, const CVector2& position)
            {
                m_fontRenderers[fontNum]->SetPosition(position);
            }

            void SetRotation(const int fontNum, const float rotation)
            {
                m_fontRenderers[fontNum]->SetRotation(rotation);
            }

            void SetPivot(const int fontNum, const CVector2& pivot)
            {
                m_fontRenderers[fontNum]->SetPivot(pivot);
            }

            void SetColor(const int fontNum, const CVector4& color)
            {
                m_fontRenderers[fontNum]->SetColor(color);
            }

            //void SetScale(const int fontNum, const CVector3& scale)
            //{
            //    m_fontRenderer->SetScale(scale);
            //}

        public: // Get function
            const CVector2& GetPosition(const int fontNum) const
            {
                return m_fontRenderers[fontNum]->GetPosition();
            }

            const float GetRotation(const int fontNum) const
            {
                return m_fontRenderers[fontNum]->GetRotation();
            }

            const CVector2& GetPivot(const int fontNum) const
            {
                return m_fontRenderers[fontNum]->GetPivot();
            }

            const CVector4& GetColor(const int fontNum) const
            {
                return m_fontRenderers[fontNum]->GetColor();
            }

            //const CVector3& GetScale(const int fontNum) const
            //{
            //    return m_fontRenderer->GetScale();
            //}



        private: // data member
            std::vector<CFontRenderer*> m_fontRenderers;
        };
    }
}