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
            void LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData);

            void NewString(std::wstring firstLineString, std::wstring secondLineString);

            void SkipToEnd();

        private:
            void Animation(); // UI�̃A�j���[�V����

            void TestStringStruct();

            //�}���`�o�C�g�����񂩂烏�C�h������
//���P�[���ˑ�
            std::wstring widen(const std::string& src);
        private: // enum


        private: // constant data member
            const char* m_kSpriteWindowFilePath = "Assets/Level2D/LevelFiles/TalkWindow.tdl";


        private: // data member
            nsLevel2D::CLevel2D m_level;

            // �{�^���̉摜
            CSpriteUI* m_spriteWindow = nullptr;
            CFontRenderer* m_talkRenderer[2] = { nullptr,nullptr };
            CFontRenderer* m_nameRenderer = nullptr;
            std::wstring m_firstLineString = L"";
            std::wstring m_secondLineString = L"";
            std::wstring m_currentStr = L"";
            std::wstring* m_writingStrPtr = &m_firstLineString;
            CFontRenderer* m_writingFontPtr = nullptr;
            std::wstring::iterator itr;
            float count = 0.0f;
            bool m_isShowAllLine = false;

            //�e�X�g
            std::list<std::vector<std::string>> m_conversationData;
            std::list<std::vector<std::string>>::iterator m_strItr;
        };
    }
}