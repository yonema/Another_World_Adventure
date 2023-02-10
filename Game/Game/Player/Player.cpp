#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Skill/ActiveSkillList.h"
#include "../UserData.h"

#ifdef _DEBUG
#include "../Monster/Monster.h"
#include "PlayerManager.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/PassiveSkill.h"
#endif
#include "../UI/Battle/Player/PlayerBattleStatusUI.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/player.fbx";	//�v���C���[���f���̃t�@�C���p�X
		constexpr float kPlayerModelScale = 0.1f;	//�v���C���[���f���̊g�嗦
		constexpr const char* const kPlayerModelTextureRootPath = "player";	//�v���C���[���f���̃e�N�X�`���̃p�X
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::StartSub() {

			//�v���C���[�Ǘ��N���X�Ɏ��g��ݒ�B
			CPlayerManager::GetInstance()->SetPlayer(this);

			//�A�j���[�V�������������B
			m_animation.Init(this, &m_input, &m_action);

			//�v���C���[���f���𐶐��B
			CreatePlayerModel();

			//�A�j���[�V�����Ɏg�p���郂�f����`����B
			m_animation.SetPlayerModelAndAnimEvent(m_modelRenderer);

			//����Ǘ��N���X���������B
			m_weaponManager.Init(m_modelRenderer);

#ifdef _DEBUG

			CPlayerManager::GetInstance()->SetWeapon("NewSword");

#endif // DEBUG

			//�X�e�[�^�X���������B
			//m_status.Init(&m_weaponManager);
			m_status.Init(m_weaponManager.GetWeaponPointer(),GetPassiveSkillManager(),GetFeatureManager());

			//���̓N���X���������B
			m_input.Init(&m_action, &m_animation);

			//�A�N�V�����N���X���������B
			m_action.Init(m_position, m_rotation, &m_status, GetFeatureManager(),&m_animation);

			//�����蔻����������B
			m_collider.Init(this);

			

#ifdef _DEBUG
			//���ɍŏ��͓Ńp�b�V�u�X�L���ɐݒ�B
			CPlayerManager::GetInstance()->SetPassiveSkill(0, "Paralysiser");

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

			// UI�̏���
			m_playerBattleStatusUI = NewGO<nsUI::CPlayerBattleStatusUI>();
			m_playerBattleStatusUI->LoadLevel();


			//�f�[�^�����[�h�B
			CUserData userData;
			userData.Load();

			//�v���C���[�Ǘ��N���X���������B
			CPlayerManager::GetInstance()->Init(this);

			return true;
		}

		void CPlayer::OnDestroySub() {

			//�v���C���[�Ǘ��N���X��j���B
			CPlayerManager::GetInstance()->DeleteInstance();

			//�A�N�V�����N���X��j���B
			m_action.Release();

			//���̓N���X��j���B
			m_input.Release();

			//�A�j���[�V������j���B
			m_animation.Release();

			//�����j���B
			m_weaponManager.Release();

			//�h���j���B
			if (m_armor != nullptr) {
				m_armor->Release();
				m_armor = nullptr;
			}

			//�����蔻���j���B
			m_collider.Release();

			// UI��j���B
			DeleteGO(m_playerBattleStatusUI);
		}

		void CPlayer::UpdateActor(float deltaTime) {

			//����ł���Ȃ�B
			if (IsDeath()) {

				//���S��ԂɁB
				m_action.SetState(EnPlayerState::enDeath);

				//�A�j���[�V�������X�V�B
				m_animation.Update(m_action.IsChangeState(), m_action.GetState());

				//�X�e�[�g�̕ύX�󋵂��������B
				m_action.ResetChangeState();

				//�R���C�_�[��j���B
				if (!m_collider.IsReleased()) {

					m_collider.Release();
				}

				//����ȏ�͉��������I���B
				return;
			}

			//���̓N���X���X�V�B
			m_input.Update(m_modelRenderer->IsPlaying());

			//�v���C���[�A�N�V�����N���X���X�V�B
			m_action.Update(deltaTime);

			//�X�e�[�^�X���X�V�B
			m_status.Update();

			//�A�j���[�V�������X�V�B
			m_animation.Update(m_action.IsChangeState(), m_action.GetState());

			//�X�e�[�g�̕ύX�󋵂��������B
			m_action.ResetChangeState();

			//����Ǘ��N���X���X�V�B
			m_weaponManager.Update();

			//�g���K�[���X�V�B
			m_collider.Update();

#ifdef _DEBUG
			//�v���C���[��HP��\���B

			size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			StringCbPrintf(m_dispText, dispTextSize, L"Level = %d , Exp = %d", m_status.GetLevel(), m_status.GetExp());
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

				//�Ђ�ݒl�����Z�B
				m_status.AddWinceValue(damage);

				//�Ђ�ݒl���Ђ�ݒl�̋�؂�𒴂��Ă�����B
				if (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

					//�_���[�W��Ԃɐݒ�B
					m_action.SetState(EnPlayerState::enDamage);

					//�N�[���^�C����ON�ɐݒ�B
					m_input.CoolTimeOn();

					//���Ђ�񂾂̂ŁA���ȏ�̂Ђ�݂͖����Ƃ���B
					while (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

						//�Ђ�ݒl�����Z�B
						m_status.SubWinceValue(m_status.GetWinceDelimiter());
					}
				}
			}

			// UIの処琁E
			m_playerBattleStatusUI->SetUIPlayerStatus(
				m_status.GetHP(), m_status.GetMaxHP(),
				m_status.GetMP(), m_status.GetMaxMP(),
				m_status.GetSP(), m_status.GetMaxSP()
			);
		}

		void CPlayer::SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill) {

			//�A�N�e�B�u�X�L����ݒ�B
			m_action.SetActiveSkill(setNum, activeSkill);
		}

		nsSkill::CActiveSkill* CPlayer::GetActiveSkill(int skillNum)const {

			//�A�N�e�B�u�X�L�����擾�B
			return m_action.GetActiveSkill(skillNum);
		}

		void CPlayer::SetWeapon(nsWeapon::CWeapon* weapon) {

			//�����ݒ�B
			m_weaponManager.ChangeWeapon(weapon);
		}

		void CPlayer::SetArmor(nsArmor::CArmor* armor) {

			//���ɖh���񂪓����Ă�����B
			if (m_armor != nullptr) {

				//�h���j���B
				m_armor->Release();
				m_armor = nullptr;
			}

			//�h���ݒ�B
			m_armor = armor;
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


			//�A�j���[�V�����̐����擾�B
			const int animNum = static_cast<int>(m_animation.GetAnimFilePath().size());

			//�A�j���[�V�����̃t�@�C���p�X�̔z����`�B
			std::vector<const char*> animNumVec;

			//�A�j���[�V�����̐������񂵂ăt�@�C���p�X���i�[�B
			for (int animIndex = 0; animIndex < animNum; animIndex++) {

				//�A�j���[�V�����̃t�@�C���p�X���擾�B
				animNumVec.emplace_back(m_animation.GetAnimFilePath()[animIndex].c_str());
			}

			//�A�j���[�V�������������B
			modelInitData.animInitData.Init(
				static_cast<unsigned int>(animNum),
				animNumVec.data()
			);

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
	}
}

