#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/hoge.fbx";	//�v���C���[���f���̃t�@�C���p�X
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::Start() {

			//�v���C���[���f���𐶐��B
			CreatePlayerModel();

			//����𐶐��B
			CreateWeapon();

			//�h��𐶐��B
			CreateArmor();

			//�X�e�[�^�X���������B
			m_status.Init();

			//���̓N���X���������B
			m_input.Init(&m_action);

			//�A�N�V�����N���X���������B
			m_action.Init();

			return true;
		}

		void CPlayer::OnDestroy() {

			//�v���C���[���f����j���B
			DeleteGO(m_modelRenderer);

			//�����j���B
			if (m_weapon != nullptr) {
				m_weapon->Release();
				m_weapon = nullptr;
			}
		}

		void CPlayer::Update(float deltaTime) {

			//�v���C���[�A�N�V�����N���X���X�V�B
			m_action.Update(deltaTime);

			//���̓N���X���X�V�B
			m_input.Update();

			//���W��ݒ�B
			m_modelRenderer->SetPosition(m_action.GetPosition());

			//��]����ݒ�B
			m_modelRenderer->SetRotation(m_action.GetRotation());
		}

		void CPlayer::ApplyDamage(int power) {

			//�K�[�h�����K�[�h�Q�[�W�̒l���З͂�荂���B
			if (m_action.GetState() == EnPlayerState::enGuard
				&& m_status.GetGuardGaugeValue() >= power
				)
			{
				//�K�[�h�����B
				//�З͕������K�[�h�Q�[�W�̒l����������B
				m_status.DamageGuardGaugeValue(power);
			}
			else {
				//�_���[�W�����炤�B
				m_status.DamageHP(power);
			}
		}

		void CPlayer::CreatePlayerModel() {

			//�v���C���[���f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�v���C���[���f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);

			//�v���C���[���f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(10.0f);
		}

		void CPlayer::CreateWeapon() {


		}

		void CPlayer::CreateArmor() {

#ifdef _DEBUG

			//�h������`�B
			nsArmor::SArmorInfo armorInfo;
			armorInfo.name = "sampleArmor";
			armorInfo.defence= 100;
			armorInfo.mind = 20;

			//�h��f���̃t�@�C���p�X���`�B�i����̓T���v���{�b�N�X���g�p...�j
			const char* armorModelFilePath = "Assets/Models/sampleBox.fbx";

			//�h����N���X���g���ĕ���𐶐��B
			nsArmor::CArmorBuilder armorBuilder;
			m_armor = armorBuilder.Create(armorInfo, armorModelFilePath);
#endif
		}
	}
}

