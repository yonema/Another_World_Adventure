#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayer;
	};

	//ユーザーデータ管理クラス
	class CUserData : nsUtils::SNoncopyable
	{
	public:
		void Save();

		void Load();

	private:
		void SaveStatus(nsPlayer::CPlayer* player);

		void SaveCanUseActiveSkillList(nsPlayer::CPlayer* player);

	private:
		std::list<std::vector<std::string>> m_userData;		//ユーザーデータ
	};
}