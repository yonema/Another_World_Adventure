#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CFontUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            constexpr CFontUI() = default;
            ~CFontUI() = default;


        public:
            // フォントデータの作成
            void LoadFont(const wchar_t* text, EnFontType fontType = static_cast<EnFontType>(0));


        public: // Set function
            void SetText(const wchar_t* text)
            {
                m_fontRenderer->SetText(text);
            }

            void SetPosition(const CVector2& position)
            {
                m_fontRenderer->SetPosition(position);
            }

            void SetRotation(const float rotation)
            {
                m_fontRenderer->SetRotation(rotation);
            }

            void SetPivot(const CVector2& pivot)
            {
                m_fontRenderer->SetPivot(pivot);
            }

            void SetColor(const CVector4& color)
            {
                m_fontRenderer->SetColor(color);
            }

            void SetScale(const float scale)
            {
                m_fontRenderer->SetScale(scale);
            }

        public: // Get function
            const CVector2& GetPosition() const
            {
                return m_fontRenderer->GetPosition();
            }

            const float GetRotation() const
            {
                return m_fontRenderer->GetRotation();
            }

            const CVector2& GetPivot() const
            {
                return m_fontRenderer->GetPivot();
            }

            const CVector4& GetColor() const
            {
                return m_fontRenderer->GetColor();
            }

            const float GetScale() const
            {
                return m_fontRenderer->GetScale();
            }



        private: // data member
            CFontRenderer* m_fontRenderer = nullptr;
        };
    }
}