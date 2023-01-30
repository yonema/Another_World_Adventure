#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CInnStorehouseWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CInnStorehouseWindowUI() = default;
            ~CInnStorehouseWindowUI() = default;

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
            static enum EnWindowNumber
            {
                enWindow_1,
                enWindow_2,
                enWindow_3,
                enWindow_4,
                enMaxWindowNumber
            };


        private: // constant data member
            static const char* m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber];


        private: // data member
            // �{�^���̉摜
            CSpriteUI* m_spriteWindow[EnWindowNumber::enMaxWindowNumber] = { nullptr };
        };
    }
}