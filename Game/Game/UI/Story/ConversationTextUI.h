#pragma once

namespace nsAWA
{
	namespace nsUI
	{
		class CConversationTextUI
		{
        public:
            void Init(const wchar_t* conversationCSVPath);

            void Update(float deltaTime);

            void Next();

            bool IsInited()
            {
                return m_isInited;
            }

        private:
            void SetCSVData(const wchar_t* conversationCSVPath);

            void NewString(std::wstring firstLineString, std::wstring secondLineString);

            void ShowNextChar();

            void ShowNextString();

            void SkipToEnd();

        private:
            bool m_isInited = false;

            CFontRenderer* m_nameRenderer = nullptr;
            CFontRenderer* m_firstLineRenderer = nullptr;
            CFontRenderer* m_secondLineRenderer = nullptr;
            std::wstring m_firstLineString = L"";
            std::wstring m_secondLineString = L"";
            std::wstring m_currentStr = L"";
            std::wstring* m_writingStrPtr = &m_firstLineString;
            CFontRenderer* m_writingFontPtr = nullptr;
            std::wstring::iterator itr;
            float count = 0.0f;
            bool m_isShowAllLine = false;

            //ƒeƒXƒg
            std::list<std::vector<std::string>> m_conversationData;
            std::list<std::vector<std::string>>::iterator m_strItr;
		};
	}
}

