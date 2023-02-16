#pragma once
namespace nsAWA
{
	namespace nsHumans
	{
		class CHuman;
		class CHumanManager;
	}
	namespace nsPlayer
	{
		class CPlayer;
	}
	namespace nsUI
	{
		class CConversationPlayerInputDisable;
	}
}

namespace nsAWA
{
	namespace nsHumans
	{
		class CTalkToPlayer : public IGameObject
		{
		private:
			static const float m_kTalkingDistance;
			static const float m_kTalkingRadAngle;
			static const char* const m_kTalkingCursorFilePath;
			static const CVector2 m_kTalkingCursorSize;
			static const float m_kTalkingCursorOffset;


		public:
			bool Start() override final;

			void Update(float deltaTime) override final;

			void OnDestroy() override final;

		public:
			constexpr CTalkToPlayer() = default;
			~CTalkToPlayer() = default;

			void Init(CHumanManager* manager);

			static void PushHookFunc(const std::function<bool(const std::string&)> hookFunc)
			{
				m_hookFuncList.emplace_back(hookFunc);
			}

		private:

			void UpdateNonTalking();

			void UpdateTalking();

			CHuman* FindTalkingHuman(
				const std::unordered_map<std::string, CHuman*>& humanMap,
				const nsPlayer::CPlayer* playerRef
			) const noexcept;

			bool UpdateTalkingCursor();

			void CheckIsTalking();

			void BuildCsvFilePath(std::string* filePathOut, unsigned int talkIdx);

		private:
			static std::list<std::function<bool(const std::string&)>> m_hookFuncList;
			CHumanManager* m_manager = nullptr;
			nsUI::CConversationPlayerInputDisable* m_conversation = nullptr;
			CSpriteRenderer* m_talkingCursorSR = nullptr;
			CHuman* m_talkingHuman = nullptr;
			bool m_isTalking = false;
		};

	}
}