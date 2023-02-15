#include "EventSetFuncPool.h"
#include "EventNameTable.h"
#include "../Scenes/OpeningScene.h"
#include "../GameLog/GameLog.h"
#include "../Humans/HumanModelRenderer.h"
#include "../Humans/HumanTable.h"
#include "../Player/Player.h"
#include "EventCut/EventCutInclude.h"

namespace nsAWA
{
	namespace nsEvent
	{
		CEventSetFuncPool::CEventSetFuncPool()
		{
			const char* eventName = GetEventNameFromTable(EnEventNameType::enGoddesAndAWTransfer);
			m_setFuncListMap[eventName].reserve(2);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					if (nsScene::COpeningScene::IsInitialOpening())
					{
						return true;
					}
					return false;
				}
			);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					static auto* eventCut = NewGO<CReceiveSkillEventCut>();
					bool next = eventCut->UpdateEventCut();
					if (next)
					{
						DeleteGO(eventCut);
						eventCut = nullptr;
					}
					return next;
				}
			);



			eventName = GetEventNameFromTable(EnEventNameType::enTrainingWithHRA);
			m_setFuncListMap[eventName].reserve(5);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					// ÉÇÉfÉãê∂ê¨
					static nsHumans::CHumanModelRenderer* humanMR = nullptr;
					if (humanMR == nullptr)
					{
						auto* player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
						humanMR = NewGO<nsHumans::CHumanModelRenderer>("Event_ChrisMR");
						auto pos = player->GetPosition() + CVector3(0.0f, 0.0f, -25.0f);
						CQuaternion rot;
						rot.SetRotationYDeg(180.0f);
						humanMR->Init(
							"Chris",
							pos,
							rot,
							nsHumans::g_kNameToModelFilePath.at("Chris")
						);
					}

					// è≠Çµë“Ç¬
					static bool start = false;
					InvokeFunc([&]() {start = true; }, 3.0f);

					return start;
				}
			);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					static auto* eventCut = NewGO<CTutorialEventCut>();
					bool next = eventCut->UpdateEventCut();
					if (next)
					{
						DeleteGO(eventCut);
						eventCut = nullptr;
					}
					return next;
				}
			);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					// è≠Çµë“Ç¬
					static bool start = false;
					InvokeFunc([&]() {start = true; }, 1.0f);
					return start;
				}
			);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					nsGameLog::CGameLog::GetInstance()->AddGameLog("20000GÇì¸éË");
					return true;
				}
			);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					static int step = 0;
					bool clear = false;
					switch (step)
					{
					case 0:
						Fade()->FadeOut(1.0f);
						InvokeFunc([&]() {step++; }, 1.0f);
						step++;
						break;
					case 1:
						break;
					case 2:
						DeleteGO(FindGO<nsHumans::CHumanModelRenderer>("Event_ChrisMR"));
						step++;
						break;
					case 3:
						Fade()->FadeIn(1.0f);
						InvokeFunc([&]() {step++; }, 1.0f);
						step++;
						break;
					case 4:
						break;
					case 5:
						clear = true;
						break;
					}
					return clear;
				}
			);




			return;
		}

		bool CEventSetFuncPool::Start()
		{
			return true;
		}

		void CEventSetFuncPool::Update(float deltaTime)
		{

			return;
		}

		void CEventSetFuncPool::OnDestroy()
		{

			return;
		}




	}
}