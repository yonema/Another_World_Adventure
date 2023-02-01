#pragma once

namespace nsAWA {
	
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

	//ゲームロードクラス
	class CLoadGame : public IGameObject
	{
	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

	private:
		nsPlayer::CPlayer* m_player = nullptr;			//プレイヤー
		nsCamera::CMainCamera* m_mainCamera = nullptr;	//メインカメラ
		nsBackGround::CBackGround* m_backGround = nullptr;	//バックグラウンド
	};
}