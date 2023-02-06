#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CButtonUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CButtonUI() = default;
            ~CButtonUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);
            /**
             * @brief �󂯎�����f�[�^�����ɑΉ������摜��ǂݍ���
             * @param buttonUINum �{�^���̉摜�̎��ʗp�ԍ�
             * @param imgData ���x���f�[�^
            */
            void LoadButtonSprite(const int buttonUINum, const nsLevel2D::SLevel2DSpriteData& imgData);

        private:
            void Animation(); // UI�̃A�j���[�V����


        public: // enum
            // �{�^���̉摜���ʗp�̗񋓌^
            enum EnButtonUI
            {
                enA,
                enB,
                enX,
                enY,
                enBL,
                enBR,
                enTL,
                enTR,
                enMaxButtonUI
            };


        private: // constant data member
            // �{�^���̉摜�̃t�@�C���p�X
            static const char* m_kSpriteButtonFilePath[EnButtonUI::enMaxButtonUI];
           
            
        private: // data member
            nsLevel2D::CLevel2D m_level;

            // �{�^���̉摜
            CSpriteUI* m_spriteButton = nullptr;
        };
    }
}