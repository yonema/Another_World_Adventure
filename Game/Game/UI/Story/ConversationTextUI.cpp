#include "YonemaEnginePreCompile.h"
#include "ConversationTextUI.h"
#include "../../CSV/CSVManager.h"

namespace nsAWA
{
	namespace nsUI
	{
		void CConversationTextUI::Init(const wchar_t* conversationCSVPath)
		{
			m_nameRenderer = NewGO<CFontRenderer>("nameRenderer");
			SFontParameter nameParam;
			nameParam.position = m_kNamePosition;
			nameParam.pivot = m_kTextPivot;
			m_nameRenderer->Init(nameParam);

			m_firstLineRenderer = NewGO<CFontRenderer>("firstLineRenderer");
			SFontParameter firstLineParam2;
			firstLineParam2.position = m_kFirstLinePosition;
			firstLineParam2.scale = m_kSentenceScale;
			firstLineParam2.pivot = m_kTextPivot;
			m_firstLineRenderer->Init(firstLineParam2, EnFontType::enConversation);

			m_secondLineRenderer = NewGO<CFontRenderer>("secondRenderer");
			SFontParameter secondLineParam2;
			secondLineParam2.position = m_kSecondLinePosition;
			secondLineParam2.scale = m_kSentenceScale;
			secondLineParam2.pivot = m_kTextPivot;
			m_secondLineRenderer->Init(secondLineParam2, EnFontType::enConversation);

			//Å‰‚É‘‚«ž‚Þæ‚Íˆês–Ú‚ÌƒŒƒ“ƒ_ƒ‰[
			m_writingFontPtr = m_firstLineRenderer;
			LoadCSVData(conversationCSVPath);

			m_isInited = true;
		}

		void CConversationTextUI::LoadCSVData(const wchar_t* conversationCSVPath)
		{
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(conversationCSVPath);
			m_conversationData = csvManager.GetCsvData();

			m_strItr = m_conversationData.begin();

			HandleNextSentence();
		}

		void CConversationTextUI::HandleNextSentence()
		{
			if ((*m_strItr).size() == 1)
			{
				std::string name = (*m_strItr)[0];

				m_nameRenderer->SetText(nsYMEngine::nsUtils::GetWideStringFromString(name).c_str());

				m_strItr++;
			}

			std::string first = ReplaceEmpty((*m_strItr)[0]);
			std::string second = ReplaceEmpty((*m_strItr)[1]);

			std::wstring wFirst = nsYMEngine::nsUtils::GetWideStringFromString(first);
			std::wstring wSecond = nsYMEngine::nsUtils::GetWideStringFromString(second);

			NewString(wFirst, wSecond);
		}

		std::string CConversationTextUI::ReplaceEmpty(std::string checkLine)
		{
			if (checkLine == "*")
			{
				return "";
			}
			else
			{
				return checkLine;
			}
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
			if (m_isInited == false)
			{
				return;
			}

			m_time += deltaTime;

			if (m_time >= 0.05f && m_isShowAllLine == false)
			{
				ShowNextChar();
			}
		}

		void CConversationTextUI::Next()
		{
			if (m_isShowAllLine)
			{
				ShowNextSentence();
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

			m_time = 0.0f;

			m_writingFontPtr->SetText(m_currentStr.c_str());
		}

		void CConversationTextUI::ShowNextSentence()
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

			HandleNextSentence();
		}

		void CConversationTextUI::SkipToEnd()
		{
			m_firstLineRenderer->SetText(m_firstLineString.c_str());
			m_secondLineRenderer->SetText(m_secondLineString.c_str());
			m_isShowAllLine = true;
		}
	}
}