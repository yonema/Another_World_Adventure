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
            void LoadButtonSprite(const int buttonUINum, LevelObjectData& imgData);

        private:
            void Animation(); // UI�̃A�j���[�V����


        public: // enum
            // �{�^���̉摜���ʗp�̗񋓌^
            static enum EnButtonUI
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
            // �{�^���̉摜
            CSpriteUI* m_spriteButton = nullptr;
        };
    }
}