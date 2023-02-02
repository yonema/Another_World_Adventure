#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CBlacksmithWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CBlacksmithWindowUI() = default;
            ~CBlacksmithWindowUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);
            /**
             * @brief �󂯎�����f�[�^�����ɑΉ������摜��ǂݍ���
             * @param buttonUINum �E�B���h�E�̎��ʗp�ԍ�
             * @param imgData ���x���f�[�^
            */
            void LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData);

        private:
            void Animation(); // UI�̃A�j���[�V����


        private: // enum
            static enum EnWindowNumber
            {
                enWindow_1,
                enWindow_2,
                enWindow_3,
                enWindow_4,
                enWindow_5,
                enMaxWindowNumber
            };


        private: // constant data member
            static const char* m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber];


        private: // data member
            nsLevel2D::CLevel2D m_level;

            // �{�^���̉摜
            CSpriteUI* m_spriteWindow[EnWindowNumber::enMaxWindowNumber] = { nullptr };
        };
    }
}