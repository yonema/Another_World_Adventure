#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

#ifdef _DEBUG
#include "../Monster/Monster.h"
#endif

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/player.fbx";	//�v���C���[���f���̃t�@�C���p�X
		constexpr float kPlayerModelScale = 0.1f;	//�v���C���[���f���̊g�嗦
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::StartSub() {

			//�A�j���[�V�������������B
			m_animation.Init();

			//�v���C���[���f���𐶐��B
			CreatePlayerModel();

			//�A�j���[�V�����Ɏg�p���郂�f����`����B
			m_animation.SetPlayerModel(m_modelRenderer);

			//����𐶐��B
			CreateWeapon();

			//�h��𐶐��B
			CreateArmor();

			//�X�e�[�^�X���������B
			m_status.Init();

			//���̓N���X���������B
			m_input.Init(&m_action, &m_animation);

			//�A�N�V�����N���X���������B
			m_action.Init(&m_status, GetItemManager());

			m_fontRenderer = NewGO<nsGraphics::nsFonts::CFontRenderer>();

#ifdef _DEBUG
			//�t�H���g�̏���ݒ�B
			nsGraphics::nsFonts::CFontRenderer::SFontParameter fontParam(
				L"",
				{0.0f,20.0f},
				nsMath::CVector4::White(),
				0.0f,
				0.5f,
				nsMath::CVector2::Zero(),
				EnAnchors::enTopLeft
			);

			//�������B
			m_fontRenderer->Init(fontParam);
#endif
			return true;
		}

		void CPlayer::OnDestroySub() {

			//�v���C���[���f����j���B
			DeleteGO(m_modelRenderer);

			//�����j���B
			if (m_weapon != nullptr) {
				m_weapon->Release();
				m_weapon = nullptr;
			}
		}

		void CPlayer::UpdateActor(float deltaTime) {

			//�v���C���[�A�N�V�����N���X���X�V�B
			m_action.Update(deltaTime);

			//���̓N���X���X�V�B
			m_input.Update(m_modelRenderer->IsPlaying());

			//�A�j���[�V�������X�V�B
			m_animation.Update();

			//���W��ݒ�B
			m_modelRenderer->SetPosition(m_action.GetPosition());

			//��]����ݒ�B
			m_modelRenderer->SetRotation(m_action.GetRotation());

#ifdef _DEBUG
			//�v���C���[��HP��\���B
			size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			StringCbPrintf(m_dispText, dispTextSize, L"HP = %3.4f", m_status.GetHP());
			m_fontRenderer->SetText(m_dispText);
#endif
		}

		void CPlayer::ApplyDamage(float power, bool canGuard) {

			//�K�[�h�����K�[�h�Q�[�W�̒l���З͂�荂���B
			if (m_action.GetState() == EnPlayerState::enGuard
				&& canGuard == true
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
				m_action.SetState(EnPlayerState::enDamage);
			}
		}

		void CPlayer::SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill) {

			//�A�N�e�B�u�X�L����ݒ�B
			m_action.SetActiveSkill(activeSkillNum, activeSkill);
		}

		void CPlayer::CreatePlayerModel() {

			//�v���C���[���f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�v���C���[���f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationZ(nsMath::YM_PI);

			//�A�j���[�V�����̃f�[�^���`�B
			const char* animFilePath[static_cast<int>(nsPlayerAnimation::CPlayerAnimation::EnAnimName::enNum)];

			//�A�j���[�V�����̐������܂킷�B
			for (int animIndex = 0; animIndex < static_cast<int>(nsPlayerAnimation::CPlayerAnimation::EnAnimName::enNum); animIndex++) {

				//�A�j���[�V���������o���A�i�[�B
				animFilePath[animIndex] = m_animation.GetAnimFilePath()[animIndex];
			}

			//�A�j���[�V�����̃f�[�^�𐶐��B
			SAnimationInitData* animData = new SAnimationInitData(
				static_cast<unsigned int>(nsPlayerAnimation::CPlayerAnimation::EnAnimName::enNum),
				animFilePath
			);
			
			//�A�j���[�V�������������B
			modelInitData.animInitData = animData;

			//�v���C���[���f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(kPlayerModelScale);
		}

		CPlayerStatus* CPlayer::GetStatus() {

			//�X�e�[�^�X���󂯎��B
			return &m_status;
		}

		nsWeapon::CWeapon* CPlayer::GetWeapon() {

			//������󂯎��B
			return m_weapon;
		}

		nsArmor::CArmor* CPlayer::GetArmor() {

			//�h����󂯎��B
			return m_armor;
		}

		void CPlayer::CreateWeapon() {

#ifdef _DEBUG
			////��������`�B
			//nsWeapon::SWeaponInfo weaponInfo;
			//weaponInfo.attack = 100;
			//weaponInfo.intelligence = 100;
			//weaponInfo.critical = 10;
			//weaponInfo.weaponType = nsWeapon::EnWeaponType::enSword;
			//weaponInfo.name = "NewSword";
			//
			////���탂�f���̃t�@�C���p�X���`�B
			//const char* weaponModelFilePath = "Assets/Models/sampleBox.fbx";
			//
			////���퐶���N���X���g���ĕ���𐶐��B
			//nsWeapon::CWeaponBuilder weaponBuilder;
			//m_weapon = weaponBuilder.Create(weaponInfo, weaponModelFilePath);
#endif
		}

		void CPlayer::CreateArmor() {

		}
	}
}

