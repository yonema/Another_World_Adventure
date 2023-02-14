#include "YonemaEnginePreCompile.h"
#include "TalkToPlayer.h"
#include "Human.h"
#include "HumanManager.h"
#include "HumanTable.h"
#include "../Player/Player.h"
#include "../UI/Story/ConversationWindowUI.h"

namespace nsAWA
{
	namespace nsHumans
	{
		const float CTalkToPlayer::m_kTalkingDistance = 20.0f;
		const float CTalkToPlayer::m_kTalkingRadAngle = nsMath::DegToRad(45.0f);
		const char* const CTalkToPlayer::m_kTalkingCursorFilePath = 
			"Assets/Images/Presets/Sapmles/200x200PNG.png";
		const CVector2 CTalkToPlayer::m_kTalkingCursorSize = { 100.0f,100.0f };
		const float CTalkToPlayer::m_kTalkingCursorOffset = 10.0f;




		bool CTalkToPlayer::Start()
		{
			return true;
		}

		void CTalkToPlayer::Update(float deltaTime)
		{
			if (m_isTalking != true)
			{
				UpdateNonTalking();
			}
			else
			{
				UpdateTalking();
			}

			return;
		}

		void CTalkToPlayer::OnDestroy()
		{
			DeleteGO(m_talkingCursorSR);
			m_talkingCursorSR = nullptr;

			return;
		}

		void CTalkToPlayer::Init(CHumanManager* manager)
		{
			m_manager = manager;

			m_talkingCursorSR = NewGO<CSpriteRenderer>("TalkingCursorSR");
			SSpriteInitData initData;
			initData.filePath = m_kTalkingCursorFilePath;
			initData.spriteSize = m_kTalkingCursorSize;
			m_talkingCursorSR->Init(initData);
			m_talkingCursorSR->SetAnchor(EnAnchors::enMiddleCenter);
			m_talkingCursorSR->SetDrawingFlag(false);

			return;
		}

		void CTalkToPlayer::UpdateNonTalking()
		{
			if (m_manager == nullptr)
			{
				return;
			}

			auto* playerRef = m_manager->GetPlayerRef();

			if (playerRef == nullptr)
			{
				return;
			}

			const auto& humanMap = m_manager->GetHumanMap();

			m_talkingHuman = FindTalkingHuman(humanMap, playerRef);

			if (UpdateTalkingCursor() != true)
			{
				return;
			}

			CheckIsTalking();

			return;
		}


		CHuman* CTalkToPlayer::FindTalkingHuman(
			const std::unordered_map<std::string, CHuman*>& humanMap,
			const nsPlayer::CPlayer* playerRef
		) const noexcept
		{
			const auto& playerPos = playerRef->GetPosition();
			const auto& playerDir = playerRef->GetForwardDirection();

			CHuman* talkingHuman = nullptr;
			float minRadAngle = FLT_MAX;

			for (const auto& human : humanMap)
			{
				if (human.second->GetEnableTalking() != true)
				{
					continue;
				}

				auto distVec = human.second->GetPosition() - playerPos;

				// まずは距離判定
				if (distVec.Length() > m_kTalkingDistance)
				{
					continue;
				}

				auto toDir = distVec;
				toDir.Normalize();
				float cos = playerDir.Dot(toDir);
				float radAngle = acosf(cos);

				// 次に前方向との角度判定
				if (radAngle > m_kTalkingRadAngle)
				{
					continue;
				}

				// 最後に最小角度判定
				if (radAngle > minRadAngle)
				{
					continue;
				}

				talkingHuman = human.second;
				minRadAngle = radAngle;
			}

			return talkingHuman;
		}

		bool CTalkToPlayer::UpdateTalkingCursor()
		{
			if (m_talkingHuman == nullptr)
			{
				m_talkingCursorSR->SetDrawingFlag(false);

				return false;
			}

			m_talkingCursorSR->SetDrawingFlag(true);

			auto pos = m_talkingHuman->GetPosition();
			pos.y += m_kTalkingCursorOffset;


			auto screenPos = MainCamera()->CalcScreenPositionFromWorldPosition(pos);
			m_talkingCursorSR->SetPosition(screenPos);


			return true;
		}

		void CTalkToPlayer::CheckIsTalking()
		{
			if (m_talkingHuman == nullptr || m_isTalking)
			{
				return;
			}

			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				m_isTalking = true;

				// 会話中、カーソルは非表示
				m_talkingCursorSR->SetDrawingFlag(false);

				// 会話ウィンドウと会話内容を生成
				m_conversationWindowUI = NewGO<nsUI::CConversationWindowUI>("TalkToPlayer");
				std::string filePath = {};
				BuildCsvFilePath(&filePath, 0);
				auto wstr = nsUtils::GetWideStringFromString(filePath);
				m_conversationWindowUI->InitConvesationCSV(wstr.c_str());
			}

			return;
		}

		void CTalkToPlayer::BuildCsvFilePath(std::string* filePathOut, unsigned int talkIdx)
		{
			const auto& name = m_talkingHuman->GetName();

			const char* filePathParts = g_kNameToCsvFilePathParts.at(name);
			char idx = '0' + talkIdx + 1;

			*filePathOut = filePathParts;
			*filePathOut += idx;
			*filePathOut += ".csv";

			return;
		}




		void CTalkToPlayer::UpdateTalking()
		{
			if (m_conversationWindowUI == nullptr)
			{
				return;
			}


			if (m_conversationWindowUI->IsEnd())
			{
				m_talkingHuman = nullptr;
				m_isTalking = false;
				DeleteGO(m_conversationWindowUI);
				m_conversationWindowUI = nullptr;
			}



			return;
		}




	}
}