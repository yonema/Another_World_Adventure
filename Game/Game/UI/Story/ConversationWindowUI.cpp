#include "YonemaEnginePreCompile.h"
#include "ConversationWindowUI.h"

#include "../SpriteUI.h"
#include <sstream>


namespace nsAWA
{
	namespace nsUI
	{

		bool CConversationWindowUI::Start()
		{
;			m_level.Load(m_kSpriteWindowFilePath);
			m_level.PlayAnimation("WindowAppear");
			m_level.PlayAnimation("ButtonAppear");
			m_talkRenderer[0] = NewGO<CFontRenderer>("fontRenderer", EnGOPriority::enMax);
			m_writingFontPtr = m_talkRenderer[0];
			m_talkRenderer[1] = NewGO<CFontRenderer>("fontRenderer", EnGOPriority::enMax);
			SFontParameter talkFontParam(
				L"",
				{ -490.0f,220.0f },
				nsMath::CVector4::White(),
				0.0f,
				0.75f,
				{ 0.0f, 0.5f },
				EnAnchors::enMiddleCenter
			);

			m_talkRenderer[0]->Init(talkFontParam,EnFontType::enConversation);
			talkFontParam.position = CVector2(-490.0f, 275.0f);
			m_talkRenderer[1]->Init(talkFontParam, EnFontType::enConversation);

			m_nameRenderer = NewGO<CFontRenderer>("fontRenderer", EnGOPriority::enMax);
			SFontParameter nameFontParam(
				L"���_",
				{ -510.0f,130.0f },
				nsMath::CVector4::White(),
				0.0f,
				1.0f,
				{ 0.0f, 0.0f },
				EnAnchors::enMiddleCenter
			);
			m_nameRenderer->Init(nameFontParam, EnFontType::enConversation);

			TestStringStruct();
			return true;
		}

		void CConversationWindowUI::TestStringStruct()
		{
			std::vector<std::string> vec1 = std::vector<std::string>({ "�ڂ��o�߂��̂ł��ˁB","�}�Șb�Ŏ�藐����������܂��񂪁A���������ĕ����Ă��������B"});
			std::vector<std::string> vec2 = std::vector<std::string>({ "���Ȃ��͖�x��������Ă���Ƃ����","�ʂ薂�Ɏh����Ď���ł��܂��܂����B" });
			std::vector<std::string> vec3 = std::vector<std::string>({ "�܂�͍����邱���͓V���݂����ȂƂ���ł��B","" });
			std::vector<std::string> vec4 = std::vector<std::string>({ "����ł��Ȃ��̑O�ɂ��鎄�����_�Ƃ������Ƃł��B","" });
			std::vector<std::string> vec5 = std::vector<std::string>({ "�܂��A���������ɂ���̂�","���̐��E�ɗ��Ă݂܂��񂩂Ƃ������҂ɗ����̂ł��B" });
			std::vector<std::string> vec6 = std::vector<std::string>({ "�������A���ŕ���o���킯�ł͂���܂���B","" });
			std::vector<std::string> vec7 = std::vector<std::string>({ "���Ȃ������̐��E�ŉ߂����̂ɍ���Ȃ��悤�ɃT�|�[�g���܂��B","" });
			std::vector<std::string> vec8 = std::vector<std::string>({ "�Ƃ������ƂŁA���Ȃ������ꂩ��s�����E�ł́A","�݂�ȃX�L���Ƃ������̂��g���܂��B" });
			std::vector<std::string> vec9 = std::vector<std::string>({ "���̃X�L�����g�����ƂŁA����������������A","���͂ȍU�����s�����肷�邱�Ƃ��ł��܂��B" });
			std::vector<std::string> vec10 = std::vector<std::string>({ "�����ŁA�]���j���Ƃ��āA","���Ȃ��ɂ̓X�L���Ƒ����i���v���[���g���܂��B" });
		
			m_conversationData.emplace_back(vec1);
			m_conversationData.emplace_back(vec2);
			m_conversationData.emplace_back(vec3);
			m_conversationData.emplace_back(vec4);
			m_conversationData.emplace_back(vec5);
			m_conversationData.emplace_back(vec6);
			m_conversationData.emplace_back(vec7);
			m_conversationData.emplace_back(vec8);
			m_conversationData.emplace_back(vec9);
			m_conversationData.emplace_back(vec10);

			m_strItr = m_conversationData.begin();

			std::string first = (*m_strItr)[0];
			std::string second = (*m_strItr)[1];

			std::wstring wFirst = widen(first);
			std::wstring wSecond = widen(second);

			NewString(wFirst, wSecond);
		}

		void CConversationWindowUI::LoadLevel(const char* tdlFilePath)
		{
			m_level.Load(m_kSpriteWindowFilePath);
		}

		void CConversationWindowUI::OnDestroy()
		{
			DeleteGO(m_spriteWindow);
		}

		void CConversationWindowUI::Update(float deltaTime)
		{
			count += deltaTime;

			if (count >= 0.05 && m_isShowAllLine == false)
			{

				itr = m_writingStrPtr->begin() + m_currentStr.length();

				if (itr != m_writingStrPtr->end())
				{
					m_currentStr += (*itr);
				}
				else if(m_writingStrPtr == &m_firstLineString)
				{
					//2��ڂւ̐؂�ւ�����
					m_writingStrPtr = &m_secondLineString;
					m_writingFontPtr = m_talkRenderer[1];
					m_currentStr = L"";
				}
				else if (itr == m_secondLineString.end())
				{
					m_isShowAllLine = true;
				}

				count = 0.0f;

				m_writingFontPtr->SetText(m_currentStr.c_str());
			}

			// ���t���[���̏�����������
			if (Keyboard()->IsTrigger(EnKeyButton::en1))
			{
				m_level.PlayAnimation("Pressed");


				return;
			}

			if (Keyboard()->IsTrigger(EnKeyButton::en2))
			{

				return;
			}

			if (Keyboard()->IsTrigger(EnKeyButton::en3))
			{
				m_level.PlayAnimation("WindowAppear");
				m_level.PlayAnimation("ButtonAppear");

				return;
			}

			if (Keyboard()->IsTrigger(EnKeyButton::en4))
			{
				m_level.PlayAnimation("WindowDisappear");
				m_level.PlayAnimation("ButtonDisappear");

				return;
			}

			if (Keyboard()->IsTrigger(EnKeyButton::enJ))
			{
				if (m_isShowAllLine)
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

					std::wstring wFirst = widen(first);
					std::wstring wSecond = widen(second);

					NewString(wFirst, wSecond);
				}
				else
				{
					SkipToEnd();
				}
			}

		}

		void CConversationWindowUI::NewString(std::wstring firstLineString, std::wstring secondLineString)
		{
			m_firstLineString = firstLineString;
			m_secondLineString = secondLineString;
			m_currentStr = L"";
			m_writingStrPtr = &m_firstLineString;
			m_writingFontPtr = m_talkRenderer[0];
			m_talkRenderer[0]->SetText(L"");
			m_talkRenderer[1]->SetText(L"");
			m_isShowAllLine = false;
		}

		void CConversationWindowUI::SkipToEnd()
		{
			m_talkRenderer[0]->SetText(m_firstLineString.c_str());
			m_talkRenderer[1]->SetText(m_secondLineString.c_str());
			m_isShowAllLine = true;
		}

		std::wstring CConversationWindowUI::widen(const std::string& src)
		{

			// SJIS �� wstring
			int iBufferSize = MultiByteToWideChar(CP_ACP, 0, src.c_str()
				, -1, (wchar_t*)NULL, 0);

			// �o�b�t�@�̎擾
			wchar_t* cpUCS2 = new wchar_t[iBufferSize];

			// SJIS �� wstring
			MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, cpUCS2
				, iBufferSize);

			// string�̐���
			std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

			// �o�b�t�@�̔j��
			delete[] cpUCS2;

			return oRet;
		}

		void CConversationWindowUI::Animation()
		{

		}
	}
}