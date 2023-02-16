#include "EventSetFuncPool.h"
#include "EventNameTable.h"
#include "EventManager.h"
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
			// OpeningScene�̏��������I������
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
			// �X�L���I�т̃C�x���g�J�b�g
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					static bool wait = true;
					InvokeFunc([&]() {wait = false; }, 1.0f);
					if (wait)
					{
						return false;
					}
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
			static constexpr const char* const kEventChrisMRName = "Event_ChrisMR";
			// ���f���̐���+�����҂�
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					// ���f������
					static nsHumans::CHumanModelRenderer* humanMR = nullptr;
					if (humanMR == nullptr)
					{
						auto* player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
						humanMR = NewGO<nsHumans::CHumanModelRenderer>(kEventChrisMRName);
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

					// �����҂�
					static bool start = false;
					InvokeFunc([&]() {start = true; }, 3.0f);

					return start;
				}
			);
			// �`���[�g���A���C�x���g�J�b�g
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
			// �����҂�
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					// �����҂�
					static bool start = false;
					InvokeFunc([&]() {start = true; }, 1.0f);
					return start;
				}
			);
			// �����Q�b�g
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					nsGameLog::CGameLog::GetInstance()->AddGameLog("20000G�����");
					return true;
				}
			);
			// �t�F�[�h+���f������
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
						DeleteGO(FindGO<nsHumans::CHumanModelRenderer>(kEventChrisMRName));
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


			eventName = GetEventNameFromTable(EnEventNameType::enTownOfAlma);
			m_setFuncListMap[eventName].reserve(2);
			static constexpr const char* const kEventGuardianMRName = "Event_GuardianMR";
			// �t�F�[�h+���̑O�܂ňړ�+�q�����f������
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					static int step = 0;
					bool clear = false;
					CQuaternion rot;
					CVector3 toGuardian(-10.0f, 0.0f, -15.0f);
					auto* player =
						FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
					const auto& utilPointMap =
						CEventManager::GetInstance()->GetEventUtilPointMap();
					auto itr = utilPointMap.find("EnterTownOfAlma");
					nsHumans::CHumanModelRenderer* humanMR = nullptr;
					CVector3 pos = CVector3::Zero();

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
						// Player�̈ʒu��ύX

						if (player && itr != utilPointMap.end())
						{
							player->SetPosition(itr->second.pos);
							player->SetRotation(itr->second.rot);
						}

						// �q���𐶐�
						humanMR = NewGO<nsHumans::CHumanModelRenderer>(kEventGuardianMRName);
						pos = player->GetPosition() + toGuardian;
						toGuardian = player->GetPosition() - pos;
						toGuardian.Normalize();
						rot.SetRotation(CVector3::Back(), toGuardian);
						humanMR->Init(
							"Guardian",
							pos,
							rot,
							nsHumans::g_kNameToModelFilePath.at("Guardian")
						);

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
			// �t�F�[�h+�q�����f������
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
						DeleteGO(FindGO<nsHumans::CHumanModelRenderer>(kEventGuardianMRName));
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


			eventName = GetEventNameFromTable(EnEventNameType::enRegisterAdventurer);
			m_setFuncListMap[eventName].reserve(3);
			// 
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					return false;
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