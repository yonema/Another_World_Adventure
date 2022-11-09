#pragma once

namespace nsAWA
{
	//エイリアス宣言
	namespace nsPlayer {
		class CPlayer;
	}
	namespace nsCamera {
		class CMainCamera;
	}

	//ゲームクラス
	class CGame : public IGameObject
	{
	private:
		static const char* const m_kGameObjectName;

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
	};

}