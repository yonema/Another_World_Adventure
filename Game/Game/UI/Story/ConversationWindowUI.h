#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CConversationWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CConversationWindowUI() = default;
            ~CConversationWindowUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);
            /**
             * @brief �󂯎�����f�[�^�����ɑΉ������摜��ǂݍ���
             * @param buttonUINum �E�B���h�E�̎��ʗp�ԍ�
             * @param imgData ���x���f�[�^
            */
            void LoadWindowSprite(const int windowNum, LevelObjectData& imgData);

        private:
            void Animation(); // UI�̃A�j���[�V����


        private: // enum


        private: // constant data member
            static const char* m_kSpriteWindowFilePath;


        private: // data member
            // �{�^���̉摜
            CSpriteUI* m_spriteWindow = nullptr;
        };
    }
}