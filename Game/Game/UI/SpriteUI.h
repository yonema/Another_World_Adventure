#pragma once
#define _UI // UI�����p�̃}�N��

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            constexpr CSpriteUI() = default;
            ~CSpriteUI() = default;


        public:
            // �摜�̓ǂݍ��ݏ���
            void LoadSprite(
                const char* tdlFilePath,
                const CVector2& spriteSize = { 100.0f,100.0f },
                const EnRendererPriority priority = EnRendererPriority::enMin,
                const EnAlphaBlendMode alphaBlendMode = EnAlphaBlendMode::enNone
                );

            void LoadInitData(
                const CVector2& position,
                const CVector2& scale,
                const CVector2& pivot
            )
            {
                m_spriteRenderer->SetPosition(position);
                m_spriteRenderer->SetScale({ scale.x,scale.y,1.0f });
                m_spriteRenderer->SetPivot(pivot);
            }


        public: // Set function
            void SetPosition(const CVector2& position)
            {
                m_spriteRenderer->SetPosition(position);
            }

            void SetPivot(const CVector2& pivot)
            {
                m_spriteRenderer->SetPivot(pivot);
            }

            void SetScale(const CVector3& scale)
            {
                m_spriteRenderer->SetScale(scale);
            }

        public: // Get function
            const CVector2& GetPosition() const
            {
                return m_spriteRenderer->GetPosition();
            }

            const CVector2& GetPivot() const
            {
                return m_spriteRenderer->GetPivot();
            }

            const CVector3& GetScale() const
            {
                return m_spriteRenderer->GetScale();
            }


            /**
             * @brief ���݂̕`��t���O���擾
             * @return 
            */
            const bool IsDrawingFlag() const
            {
                return m_spriteRenderer->IsDrawingFlag();
            }

            /**
             * @brief �`�悷�邩�ǂ����̃t���O��ύX
             * @param isDrawingFlag 
            */
            void SetDrawingFlag(const bool isDrawingFlag)
            {
                m_spriteRenderer->SetDrawingFlag(isDrawingFlag);
            }


        public:
            void SetMenuUpdate()
            {
                SetFlagUpdateTable(EnMenuUpdateFlagTable::enMenu);

                m_spriteRenderer->SetMenuUpdate();
            }


        private: // data member
            CSpriteRenderer* m_spriteRenderer = nullptr; // UI�̉摜�f�[�^
        };
    }
}