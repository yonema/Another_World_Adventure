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
		constexpr const char* const kPlayerModelTextureRootPath = "player";	//�v���C���[���f���̃e�N�X�`���̃p�X
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::StartSub() {

			//�A�j���[�V�������������B
			m_animation.Init(&m_input);

			//�v���C���[���f���𐶐��B
			CreatePlayerModel();

			//�A�j���[�V�����Ɏg�p���郂�f����`����B
			m_animation.SetPlayerModelAndAnimEvent(m_modelRenderer);

			//����Ǘ��N���X���������B
			m_weaponManager.Init(m_modelRenderer);

			//����𐶐��B
			CreateWeapon();

			//�h��𐶐��B
			CreateArmor();

			//�X�e�[�^�X���������B
			m_status.Init();

			//���̓N���X���������B
			m_input.Init(&m_action, &m_animation);

			//�A�N�V�����N���X���������B
			m_action.Init(&m_status, GetItemManager(), GetFeatureManager());

			//�����蔻����������B
			m_collider.Init(this);

#ifdef _DEBUG
			m_fontRenderer = NewGO<nsGraphics::nsFonts::CFontRenderer>();

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
			m_weaponManager.Release();

			//�h���j���B
			if (m_armor != nullptr) {
				m_armor->Release();
				m_armor = nullptr;
			}

			//�����蔻���j���B
			m_collider.Release();
		}

		void CPlayer::UpdateActor(float deltaTime) {

			//�v���C���[�A�N�V�����N���X���X�V�B
			m_action.Update(deltaTime);

			//���̓N���X���X�V�B
			m_input.Update(m_modelRenderer->IsPlaying());

			//�A�j���[�V�������X�V�B
			m_animation.Update(m_action.IsChangeState(), m_action.GetState());

			//����Ǘ��N���X���X�V�B
			m_weaponManager.Update();

			//���W��ݒ�B
			m_modelRenderer->SetPosition(m_action.GetPosition());

			//��]����ݒ�B
			m_modelRenderer->SetRotation(m_action.GetRotation());

			//�g���K�[���X�V�B
			m_collider.Update();

#ifdef _DEBUG
			//�v���C���[��HP��\���B
			size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			StringCbPrintf(m_dispText, dispTextSize, L"HP = %3.4f %s", m_status.GetHP(),m_input.GetCoolTime() ? L"true" : L"false");
			m_fontRenderer->SetText(m_dispText);
#endif
		}

		void CPlayer::ApplyDamage(float damage, float power, bool canGuard) {

			//�K�[�h�����K�[�h�ł���U���Ȃ�B
			if (m_action.GetState() == EnPlayerState::enGuard
				&& canGuard == true
				)
			{
				//�K�[�h�����B
				//�З͕������K�[�h�Q�[�W�̒l����������B
				m_status.DamageGuardGaugeValue(power);

				//�K�[�h�Q�[�W��0�ɂȂ�����B
				if (fabsf(m_status.GetGuardGaugeValue()) < FLT_EPSILON) {
					
					//�X�^����Ԃɂ���B
					m_action.SetState(EnPlayerState::enStun);
				}
			}
			else {
				//�_���[�W�����炤�B
				m_status.DamageHP(damage);
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
			modelInitData.textureRootPath = kPlayerModelTextureRootPath;
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
			return m_weaponManager.GetWeapon();
		}

		nsArmor::CArmor* CPlayer::GetArmor() {

			//�h����󂯎��B
			return m_armor;
		}

		void CPlayer::CreateWeapon() {

#ifdef _DEBUG
			//��������`�B
			nsWeapon::SWeaponInfo weaponInfo;
			weaponInfo.attack = 100;
			weaponInfo.intelligence = 100;
			weaponInfo.critical = 10;
			weaponInfo.weaponType = nsWeapon::EnWeaponType::enSword;
			weaponInfo.name = "NewSword";
			
			//�������ݒ�B
			m_weaponManager.ChangeWeapon(weaponInfo);
#endif
		}

		void CPlayer::CreateArmor() {

		}
	}
}

