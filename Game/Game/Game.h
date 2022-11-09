#pragma once

namespace nsAWA
{
	//�G�C���A�X�錾
	namespace nsPlayer {
		class CPlayer;
	}
	namespace nsCamera {
		class CMainCamera;
	}

	//�Q�[���N���X
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
		nsPlayer::CPlayer* m_player = nullptr;			//�v���C���[
		nsCamera::CMainCamera* m_mainCamera = nullptr;	//���C���J����
	};

}