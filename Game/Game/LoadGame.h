#pragma once

namespace nsAWA {
	
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

	//�Q�[�����[�h�N���X
	class CLoadGame : public IGameObject
	{
	public:
		bool Start() override final;

		void Update(float deltaTime) override final;

		void OnDestroy() override final;

		void SetPlayerSpawnPosition(const CVector3& position)
		{
			m_playerSpawnPosition = position;
		}

	private:
		void CreateGameList();

		void DeleteGameList();

	private:
		nsPlayer::CPlayer* m_player = nullptr;			//�v���C���[
		nsCamera::CMainCamera* m_mainCamera = nullptr;	//���C���J����
		nsBackGround::CBackGround* m_backGround = nullptr;	//�o�b�N�O���E���h
		CVector3 m_playerSpawnPosition = nsMath::CVector3::Zero();
	};
}