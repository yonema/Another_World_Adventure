#pragma once

namespace nsAWA
{
	//前方宣言
	namespace nsPlayer {
		class CPlayer;
	}
	namespace nsCamera {
		class CMainCamera;
	}
	namespace nsBackGround {

		class CBackGround;
	}

	//ゲームクラス
	class CGame : public IGameObject
	{
	private:
		static const char* const m_kGameObjectName;		//ゲームクラスの名前

	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	public:
		constexpr CGame() = default;
		~CGame() = default;

	private:
		nsPlayer::CPlayer* m_player = nullptr;			//プレイヤー
		nsCamera::CMainCamera* m_mainCamera = nullptr;	//メインカメラ
		nsBackGround::CBackGround* m_backGround = nullptr;	//バックグラウンド
	};
}