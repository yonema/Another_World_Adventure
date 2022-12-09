#pragma once

namespace nsAWA
{
	//�O���錾
	namespace nsPlayer {
		class CPlayer;
	}
	namespace nsCamera {
		class CMainCamera;
	}
	namespace nsBackGround {

		class CBackGround;
	}

	//�Q�[���N���X
	class CGame : public IGameObject
	{
	private:
		static const char* const m_kGameObjectName;		//�Q�[���N���X�̖��O

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
		nsBackGround::CBackGround* m_backGround = nullptr;	//�o�b�N�O���E���h
	};
}