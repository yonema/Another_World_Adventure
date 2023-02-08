#include "YonemaEnginePreCompile.h"
#include "ConversationTextUI.h"
#include "../../CSV/CSVManager.h"

namespace nsAWA
{
	namespace nsUI
	{
		void CConversationTextUI::Init(const wchar_t* conversationCSVPath)
		{
			m_firstLineRenderer = NewGO<CFontRenderer>("firstLineRenderer");
			m_writingFontPtr = m_firstLineRenderer;
			m_secondLineRenderer = NewGO<CFontRenderer>("secondRenderer");
			SFontParameter talkFontParam(
				L"",
				{ -490.0f,220.0f },
				nsMath::CVector4::White(),
				0.0f,
				0.75f,
				{ 0.0f, 0.5f },
				EnAnchors::enMiddleCenter
			);

			m_firstLineRenderer->Init(talkFontParam, EnFontType::enConversation);
			talkFontParam.position = CVector2(-490.0f, 275.0f);
			m_secondLineRenderer->Init(talkFontParam, EnFontType::enConversation);

			m_nameRenderer = NewGO<CFontRenderer>("fontRenderer", EnGOPriority::enMax);
			SFontParameter nameFontParam(
				L"–¼‘O",
				{ -510.0f,130.0f },
				nsMath::CVector4::White(),
				0.0f,
				1.0f,
				{ 0.0f, 0.0f },
				EnAnchors::enMiddleCenter
			);
			m_nameRenderer->Init(nameFontParam, EnFontType::enConversation);

			SetCSVData(conversationCSVPath);

			m_isInited = true;
		}

		void CConversationTextUI::SetCSVData(const wchar_t* conversationCSVPath)
		{
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(conversationCSVPath);
			m_conversationData = csvManager.GetCsvData();

			m_strItr = m_conversationData.begin();

			std::string first = (*m_strItr)[0];
			std::string second = (*m_strItr)[1];

			std::wstring wFirst = nsYMEngine::nsUtils::GetWideStringFromString(first);
			std::wstring wSecond = nsYMEngine::nsUtils::GetWideStringFromString(second);

			NewString(wFirst, wSecond);
		}

		void CConversationTextUI::NewString(std::wstring firstLineString, std::wstring secondLineString)
		{
			m_firstLineString = firstLineString;
			m_secondLineString = secondLineString;
			m_currentStr = L"";
			m_writingStrPtr = &m_firstLineString;
			m_writingFontPtr = m_firstLineRenderer;
			m_firstLineRenderer->SetText(L"");
			m_secondLineRenderer->SetText(L"");
			m_isShowAllLine = false;
		}

		void CConversationTextUI::Update(float deltaTime)
		{
			count += deltaTime;

			if (count >= 0.05 && m_isShowAllLine == false)
			{
				ShowNextChar();
			}
		}

		void CConversationTextUI::Next()
		{
			if (m_isShowAllLine)
			{
				ShowNextString();
			}
			else
			{
				SkipToEnd();
			}
		}

		void CConversationTextUI::ShowNextChar()
		{
			itr = m_writingStrPtr->begin() + m_currentStr.length();

			if (itr != m_writingStrPtr->end())
			{
				m_currentStr += (*itr);
			}
			else if (m_writingStrPtr == &m_firstLineString)
			{
				//2—ñ–Ú‚Ö‚ÌØ‚è‘Ö‚¦ˆ—
				m_writingStrPtr = &m_secondLineString;
				m_writingFontPtr = m_secondLineRenderer;
				m_currentStr = L"";
			}
			else if (itr == m_secondLineString.end())
			{
				m_isShowAllLine = true;
			}

			count = 0.0f;

			m_writingFontPtr->SetText(m_currentStr.c_str());
		}

		void CConversationTextUI::ShowNextString()
		{
			auto end = m_conversationData.end();
			end--;

			if (m_strItr == end)
			{
				return;
			}
			else
			{
				m_strItr++;
			}

			std::string first = (*m_strItr)[0];
			std::string second = (*m_strItr)[1];


			std::wstring wFirst = nsYMEngine::nsUtils::GetWideStringFromString(first);
			std::wstring wSecond = nsYMEngine::nsUtils::GetWideStringFromString(second);

			NewString(wFirst, wSecond);
		}

		void CConversationTextUI::SkipToEnd()
		{
			m_firstLineRenderer->SetText(m_firstLineString.c_str());
			m_secondLineRenderer->SetText(m_secondLineString.c_str());
			m_isShowAllLine = true;
		}
	}
}