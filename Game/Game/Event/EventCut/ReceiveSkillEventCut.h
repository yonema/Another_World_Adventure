#pragma once
#include "EventCutBase.h"
#include "../../CSV/CSVManager.h"

namespace nsAWA 
{
	namespace nsSkill 
	{
		struct SActiveSkillData;
		struct SPassiveSkillData;
	}

	namespace nsMagic
	{
		struct SMagicData;
	}

}


namespace nsAWA
{
	namespace nsEvent
	{
		class CReceiveSkillEventCut : public IEventCutBase
		{
		private:
			static float m_kSkillPosWidth;
			static float m_kInputAxisThreshold;
			static const char* const m_kExceptionName[];
			static const char* const m_kCursorSpriteFilePath;
			static const float m_kCursorXPos;
			static const float m_kStartYPos;
			static const wchar_t* const m_kTitleText[];
			static const CVector4 m_kFontColor;
			
		private:
			enum EnStep
			{
				enSelectActiveSkill_1,
				enCheckActiveSkill_1,
				enSelectActiveSkill_2,
				enCheckActiveSkill_2,
				enSelectMagicSkill,
				enCheckMagicSkill,
				enSelectPassiveSkill,
				enCheckPassiveSkill
			};
		public:
			bool UpdateEventCut() noexcept override final;

		public:
			CReceiveSkillEventCut();
			~CReceiveSkillEventCut();

		private:
			void Progress() noexcept;

			void Regress() noexcept;

			void SelectSkill(const std::vector<CFontRenderer*>& selectFR);

			void HiddenAllFont();

			void HiddenFont(const std::vector<CFontRenderer*>& frArray);

			void DisplayStepFont();

			void DisplayFont(const std::vector<CFontRenderer*>& frArray);

			void DisplayCheckFont(const wchar_t* name);

			void HiddenCheckFont();

			void CheckSkill();

			void RegisterSelectedIdx();

			void SaveSkillData();

		private:
			std::vector<CFontRenderer*> m_activeSkillListFR = {};
			std::vector<CFontRenderer*> m_magicSkillListFR = {};
			std::vector<CFontRenderer*> m_passiveSkillListFR = {};
			std::vector<std::string> m_activeSkillNameArray = {};
			std::vector<std::string> m_magicSkillNameArray = {};
			std::vector<std::string> m_passiveSkillNameArray = {};
			CFontRenderer* m_titleFR = nullptr;
			CSpriteRenderer* m_titleBackWindow = nullptr;
			CSpriteRenderer* m_backWindow = nullptr;
			EnStep m_step = EnStep::enSelectActiveSkill_1;
			CSpriteRenderer* m_cursorSR = nullptr;

			CFontRenderer* m_checkSkillFR = nullptr;
			CFontRenderer* m_yesFR = nullptr;
			CFontRenderer* m_noFR = nullptr;
			CSpriteRenderer* m_checkBackWindow = nullptr;
			bool m_isYes = true;

			bool m_isPress = false;

			int m_currentIdx = 0;

			int m_selectedActiveSkill_1Idx = 0;
			int m_selectedActiveSkill_2Idx = 0;
			int m_selectedMagicSkill_1Idx = 0;
			int m_selectedPassiveSkill_1Idx = 0;

			nsCSV::CCsvManager m_saveCSVData = {};
		};

	}
}