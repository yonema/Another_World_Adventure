#include "ReceiveSkillEventCut.h"
#include "../../Skill/ActiveSkillList.h"
#include "../../Skill/PassiveSkillList.h"
#include "../../Magic/MagicList.h"
#include "../../Player/PlayerManager.h"

namespace nsAWA
{
	namespace nsEvent
	{
		float CReceiveSkillEventCut::m_kSkillPosWidth = 50.0f;
		float CReceiveSkillEventCut::m_kInputAxisThreshold = 0.3f;
		const char* const CReceiveSkillEventCut::m_kExceptionName[] =
		{
			"WeakAttack_A",
			"WeakAttack_B",
			"WeakAttack_C",
			"StrongAttack"
		};
		const char* const CReceiveSkillEventCut::m_kCursorSpriteFilePath =
			"Assets/Images/Institution/Guild/Arrow.png";
		const float CReceiveSkillEventCut::m_kCursorXPos = -200.0f;
		const float CReceiveSkillEventCut::m_kStartYPos = 170.0f;
		const float CReceiveSkillEventCut::m_kStartYTitleOffset = 60.0f;


		const wchar_t* const CReceiveSkillEventCut::m_kTitleText[] =
		{
			L"1つ目の武技スキルを選択してください。",
			L"2つ目の武技スキルを選択してください。",
			L"魔法スキルを選択してください。",
			L"パッシブスキルを選択してください。"
		};
		const CVector4 CReceiveSkillEventCut::m_kFontColor = CVector4::White();


		CReceiveSkillEventCut::CReceiveSkillEventCut()
		{
			const auto& activeSkillList = 
				nsSkill::CActiveSkillList::GetInstance()->GetActiveSkillList();

			const auto& magicList = nsMagic::CMagicList::GetInstance()->GetMagicList();

			const auto& passiveSkillList = 
				nsSkill::CPassiveSkillList::GetInstance()->GetPassiveSkillList();

			SFontParameter fontParam;
			fontParam.anchor = EnAnchors::enTopCenter;
			fontParam.pivot = { 0.5f,0.5f };
			fontParam.color = m_kFontColor;

			m_activeSkillListFR.reserve(activeSkillList.size());
			m_activeSkillNameArray.reserve(activeSkillList.size());
			int idx = 0;
			for (const auto& activeSkill : activeSkillList)
			{
				bool exception = false;
				for (int i = 0; i < _countof(m_kExceptionName); i++)
				{
					if (activeSkill.name == std::string(m_kExceptionName[i]))
					{
						exception = true;
						break;
					}
				}
				if (exception)
				{
					continue;
				}
				fontParam.text = nsUtils::GetWideStringFromString(activeSkill.name);
				fontParam.position = { 0.0f, m_kStartYPos + m_kSkillPosWidth * idx };
				auto* fr = NewGO<CFontRenderer>();
				fr->Init(fontParam);
				m_activeSkillListFR.emplace_back(fr);
				m_activeSkillNameArray.emplace_back(activeSkill.name);

				idx++;
			}
			idx = 0;
			m_magicSkillListFR.reserve(magicList.size());
			m_magicSkillNameArray.reserve(magicList.size());
			for (const auto& magicSkill : magicList)
			{
				fontParam.text = nsUtils::GetWideStringFromString(magicSkill.name);
				fontParam.position = { 0.0f, m_kStartYPos + m_kSkillPosWidth * idx };
				auto* fr = NewGO<CFontRenderer>();
				fr->Init(fontParam);
				m_magicSkillListFR.emplace_back(fr);
				m_magicSkillNameArray.emplace_back(magicSkill.name);

				idx++;
			}
			idx = 0;
			m_passiveSkillListFR.reserve(passiveSkillList.size());
			m_passiveSkillNameArray.reserve(passiveSkillList.size());
			for (const auto& passiveSkill : passiveSkillList)
			{
				fontParam.text = nsUtils::GetWideStringFromString(passiveSkill.name);
				fontParam.position = { 0.0f, m_kStartYPos + m_kSkillPosWidth * idx };
				auto* fr = NewGO<CFontRenderer>();
				fr->Init(fontParam);
				m_passiveSkillListFR.emplace_back(fr);
				m_passiveSkillNameArray.emplace_back(passiveSkill.name);

				idx++;
			}

			{
				SFontParameter param = {};
				param.text = m_kTitleText[0];
				param.anchor = EnAnchors::enTopCenter;
				param.pivot = { 0.5f,1.0f };
				param.color = m_kFontColor;
				param.position = { 0.0f, m_kStartYPos - m_kStartYTitleOffset };
				m_titleFR = NewGO<CFontRenderer>();
				m_titleFR->Init(param);
			}

			{
				SSpriteInitData initData = {};
				initData.filePath = "Assets/Images/SkillFromGoddess/BackWindow.png";
				initData.spriteSize = { 470.0f * 1.2f, 560.0f * 1.0f };
				initData.alphaBlendMode = EnAlphaBlendMode::enTrans;
				m_backWindow = NewGO<CSpriteRenderer>();
				m_backWindow->Init(initData);
				m_backWindow->SetPosition({ 0.0f, 60.0f });
			}

			{
				SSpriteInitData initData = {};
				initData.filePath = "Assets/Images/SkillFromGoddess/TitleBackWindow.png";
				initData.spriteSize = { 500.0f * 1.75f, 160.0f * 0.75f };
				initData.alphaBlendMode = EnAlphaBlendMode::enTrans;
				m_titleBackWindow = NewGO<CSpriteRenderer>();
				m_titleBackWindow->Init(initData);
				m_titleBackWindow->SetAnchor(EnAnchors::enTopCenter);
				m_titleBackWindow->SetPosition(
					{ 0.0f,  m_kStartYPos - m_kStartYTitleOffset - 20.0f });
			}

			{
				SSpriteInitData initData = {};
				initData.filePath = "Assets/Images/SkillFromGoddess/BackWindow.png";
				initData.spriteSize = { 470.0f * 1.25, 560.0f * 0.75 };
				initData.alphaBlendMode = EnAlphaBlendMode::enTrans;
				m_checkBackWindow = NewGO<CSpriteRenderer>();
				m_checkBackWindow->Init(initData);
				m_checkBackWindow->SetPosition({ 0.0f, 0.0f });
				m_checkBackWindow->SetDrawingFlag(false);
			}


			m_cursorSR = NewGO<CSpriteRenderer>();
			SSpriteInitData spriteInitData = {};
			spriteInitData.filePath = m_kCursorSpriteFilePath;
			spriteInitData.spriteSize = { 48.0f, 48.0f };
			spriteInitData.alphaBlendMode = EnAlphaBlendMode::enTrans;
			m_cursorSR->Init(spriteInitData);
			m_cursorSR->SetAnchor(EnAnchors::enTopCenter);
			m_cursorSR->SetPivot({ 1.0f,0.5f });
			m_cursorSR->SetPosition({ m_kCursorXPos, m_kStartYPos });
			m_cursorSR->SetScale(1.5f);


			HiddenAllFont();

			DisplayFont(m_activeSkillListFR);

			SFontParameter selectedFontParam;
			selectedFontParam.anchor = EnAnchors::enMiddleCenter;
			selectedFontParam.pivot = { 0.5f,0.5f };
			selectedFontParam.color = m_kFontColor;
			selectedFontParam.scale = 0.0f;
			selectedFontParam.position = { 0.0f,-50.0f };
			m_checkSkillFR = NewGO<CFontRenderer>();
			m_checkSkillFR->Init(selectedFontParam);

			selectedFontParam.text = L"はい";
			selectedFontParam.position = { -150.0f, 50.0f };
			m_yesFR = NewGO<CFontRenderer>();
			m_yesFR->Init(selectedFontParam);

			selectedFontParam.text = L"いいえ";
			selectedFontParam.position = { 150.0f, 50.0f };
			m_noFR = NewGO<CFontRenderer>();
			m_noFR->Init(selectedFontParam);

			return;
		}



		CReceiveSkillEventCut::~CReceiveSkillEventCut()
		{
			for (auto& fr : m_activeSkillListFR)
			{
				DeleteGO(fr);
				fr = nullptr;
			}
			m_activeSkillListFR.clear();

			for (auto& fr : m_magicSkillListFR)
			{
				DeleteGO(fr);
				fr = nullptr;
			}
			m_magicSkillListFR.clear();

			for (auto& fr : m_passiveSkillListFR)
			{
				DeleteGO(fr);
				fr = nullptr;
			}
			m_passiveSkillListFR.clear();

			DeleteGO(m_cursorSR);
			m_cursorSR = nullptr;

			DeleteGO(m_checkSkillFR);
			m_checkSkillFR = nullptr;
			DeleteGO(m_yesFR);
			m_yesFR = nullptr;
			DeleteGO(m_noFR);
			m_noFR = nullptr;
			DeleteGO(m_titleFR);
			m_titleFR = nullptr;
			DeleteGO(m_titleBackWindow);
			m_titleBackWindow = nullptr;
			DeleteGO(m_backWindow);
			m_backWindow = nullptr;
			DeleteGO(m_checkBackWindow);
			m_checkBackWindow = nullptr;


			return;
		}



		bool CReceiveSkillEventCut::UpdateEventCut() noexcept
		{
			bool clear = false;
			switch (m_step)
			{
			case EnStep::enSelectActiveSkill_1:
				SelectSkill(m_activeSkillListFR);
				break;
			case EnStep::enCheckActiveSkill_1:
				CheckSkill();
				break;
			case EnStep::enSelectActiveSkill_2:
				SelectSkill(m_activeSkillListFR);
				break;
			case EnStep::enCheckActiveSkill_2:
				CheckSkill();
				break;
			case EnStep::enSelectMagicSkill:
				SelectSkill(m_magicSkillListFR);
				break;
			case EnStep::enCheckMagicSkill:
				CheckSkill();
				break;
			case EnStep::enSelectPassiveSkill:
				SelectSkill(m_passiveSkillListFR);
				break;
			case EnStep::enCheckPassiveSkill:
				CheckSkill();
				break;
			default:
				SaveSkillData();
				clear = true;
				break;
			}


			return clear;
		}

		void CReceiveSkillEventCut::SelectSkill(const std::vector<CFontRenderer*>& selectFR)
		{
			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				if (m_step == EnStep::enSelectActiveSkill_2)
				{
					if (m_currentIdx == m_selectedActiveSkill_1Idx)
					{
						return;
					}
				}
				Progress();
				HiddenAllFont();
				DisplayCheckFont(selectFR[m_currentIdx]->GetText().c_str());
			}

			float inputF = Input()->GetVirtualAxis(EnAxisMapping::enForward);
			if (fabsf(inputF) <= m_kInputAxisThreshold)
			{
				m_isPress = false;
				return;
			}

			if (m_isPress)
			{
				return;
			}

			m_isPress = true;

			if (inputF > 0.0f)
			{
				m_currentIdx--;
			}
			else
			{
				m_currentIdx++;
			}

			if (m_currentIdx < 0)
			{
				m_currentIdx = 0;
			}
			else if (m_currentIdx >= static_cast<int>(selectFR.size()))
			{
				m_currentIdx = static_cast<int>(selectFR.size() - 1);
			}

			m_cursorSR->SetPosition(
				{ m_kCursorXPos, m_kStartYPos + m_kSkillPosWidth * m_currentIdx });




			return;
		}


		void CReceiveSkillEventCut::Progress() noexcept
		{
			int iStep = static_cast<int>(m_step);
			iStep++;
			m_step = static_cast<EnStep>(iStep);



			return;
		}

		void CReceiveSkillEventCut::Regress() noexcept
		{
			int iStep = static_cast<int>(m_step);
			iStep--;
			m_step = static_cast<EnStep>(iStep);




			return;
		}

		void CReceiveSkillEventCut::HiddenAllFont()
		{
			HiddenFont(m_activeSkillListFR);
			HiddenFont(m_magicSkillListFR);
			HiddenFont(m_passiveSkillListFR);
			m_titleFR->SetScale(0.0f);

			m_titleBackWindow->SetDrawingFlag(false);
			m_backWindow->SetDrawingFlag(false);

			return;
		}

		void CReceiveSkillEventCut::HiddenFont(const std::vector<CFontRenderer*>& frArray)
		{
			for (auto& fr : frArray)
			{
				fr->SetScale(0.0f);
			}
			return;
		}

		void CReceiveSkillEventCut::DisplayStepFont()
		{
			switch (m_step)
			{
			case EnStep::enSelectActiveSkill_1:
				m_titleFR->SetText(m_kTitleText[0]);
				DisplayFont(m_activeSkillListFR);
				break;
			case EnStep::enSelectActiveSkill_2:
				m_titleFR->SetText(m_kTitleText[1]);
				DisplayFont(m_activeSkillListFR);
				break;
			case EnStep::enSelectMagicSkill:
				m_titleFR->SetText(m_kTitleText[2]);
				DisplayFont(m_magicSkillListFR);
				break;
			case EnStep::enSelectPassiveSkill:
				m_titleFR->SetText(m_kTitleText[3]);
				DisplayFont(m_passiveSkillListFR);
				break;
			}
		}

		void CReceiveSkillEventCut::DisplayFont(const std::vector<CFontRenderer*>& frArray)
		{
			for (auto& fr : frArray)
			{
				fr->SetScale(1.0f);
			}
			m_titleFR->SetScale(1.0f);
			m_titleBackWindow->SetDrawingFlag(true);
			m_backWindow->SetDrawingFlag(true);
			return;
		}


		void CReceiveSkillEventCut::DisplayCheckFont(const wchar_t* name)
		{
			m_checkSkillFR->SetText(name);
			m_checkSkillFR->SetScale(1.0f);

			m_yesFR->SetScale(1.0f);
			m_noFR->SetScale(1.0f);

			m_isYes = true;
			auto pos = m_yesFR->GetPosition();
			pos.x -= 50.0f;
			m_cursorSR->SetPosition(pos);
			m_cursorSR->SetAnchor(m_yesFR->GetAnchor());

			m_checkBackWindow->SetDrawingFlag(true);


			return;
		}

		void CReceiveSkillEventCut::CheckSkill()
		{
			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				if (m_isYes)
				{
					RegisterSelectedIdx();

					Progress();
				}
				else
				{
					Regress();
				}

				m_cursorSR->SetAnchor(EnAnchors::enTopCenter);
				m_cursorSR->SetPosition(
					{ m_kCursorXPos, m_kStartYPos + m_kSkillPosWidth * m_currentIdx });
				DisplayStepFont();
				HiddenCheckFont();
			}

			float inputF = Input()->GetVirtualAxis(EnAxisMapping::enRight);
			if (fabsf(inputF) <= m_kInputAxisThreshold)
			{
				m_isPress = false;
				return;
			}

			if (m_isPress)
			{
				return;
			}

			m_isPress = true;

			CVector2 pos = CVector2::Zero();
			if (inputF > 0.0f)
			{
				m_isYes = false;
				pos = m_noFR->GetPosition();
			}
			else
			{
				m_isYes = true;
				pos = m_yesFR->GetPosition();
			}

			pos.x -= 50.0f;
			m_cursorSR->SetPosition(pos);



			return;
		}


		void CReceiveSkillEventCut::HiddenCheckFont()
		{

			m_checkSkillFR->SetScale(0.0f);

			m_yesFR->SetScale(0.0f);
			m_noFR->SetScale(0.0f);

			m_checkBackWindow->SetDrawingFlag(false);

			return;
		}

		void CReceiveSkillEventCut::RegisterSelectedIdx()
		{
			switch (m_step)
			{
			case EnStep::enCheckActiveSkill_1:
				m_selectedActiveSkill_1Idx = m_currentIdx;
				break;
			case EnStep::enCheckActiveSkill_2:
				m_selectedActiveSkill_2Idx = m_currentIdx;
				break;
			case EnStep::enCheckMagicSkill:
				m_selectedMagicSkill_1Idx = m_currentIdx;
				break;
			case EnStep::enCheckPassiveSkill:
				m_selectedPassiveSkill_1Idx = m_currentIdx;
				break;
			}

			m_currentIdx = 0;

			return;
		}

		void CReceiveSkillEventCut::SaveSkillData()
		{
			m_saveCSVData.LoadCSV(L"Assets/CSV/UserData.csv");

			auto data = m_saveCSVData.GetCsvData();
			auto itr = data.begin();

			for (int i = 0; i < 4; i++)
			{
				itr++;
			}
			(*itr)[0] = m_activeSkillNameArray[m_selectedActiveSkill_1Idx];
			(*itr)[1] = m_activeSkillNameArray[m_selectedActiveSkill_2Idx];
			(*itr)[2] = m_magicSkillNameArray[m_selectedMagicSkill_1Idx];
			itr++;
			(*itr)[0] = m_passiveSkillNameArray[m_selectedPassiveSkill_1Idx];
			m_saveCSVData.SaveCSV(L"Assets/CSV/UserData.csv", data);

			return;
		}




	}
}