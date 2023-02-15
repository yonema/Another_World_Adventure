#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Skill/ActiveSkillList.h"
#include "../UserData.h"
#include "PlayerManager.h"
#include "../Humans/HumanTable.h"

#ifdef _DEBUG
#include "../Monster/Monster.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/PassiveSkill.h"
#endif
#include "../UI/Battle/Player/PlayerBattleStatusUI.h"
#include "../UI/Battle/Skill/SkillIconUI.h"
#include "../UI/Battle/Item/ItemUI.h"
#include "../UI/Menu/MenuManager.h"

namespace nsAWA {

	namespace {

		//constexpr const char* const kPlayerModelFilePath = "Assets/Models/player.fbx";	//�v���C���[���f���̃t�@�C���p�X
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
			DeleteGO(m_skillIconUI);
			DeleteGO(m_menuManager);
		}

		void CPlayer::UpdateActor(float deltaTime) {

			if (m_isInited != true)
			{
				InitAfterLoadModel();

				return;
			}

			//����ł���Ȃ�B
			if (IsDeath()) {

				//���S��ԂɁB
				m_action.SetState(EnPlayerState::enDeath);

				//�A�j���[�V�������X�V�B
				m_animation.Update(m_action.IsChangeState(), m_action.GetState());

				//�X�e�[�g�̕ύX�󋵂��������B
				m_action.ResetChangeState();

				//����Ǘ��N���X���X�V�B
				m_weaponManager.Update();

				//�R���C�_�[��j���B
				if (!m_collider.IsReleased()) {

					m_collider.Release();
				}

				// UI�Ƀv���C���[�̃X�e�[�^�X��n��
				m_playerBattleStatusUI->SetUIPlayerStatus(
					m_status.GetHP(), m_status.GetMaxHP(),
					m_status.GetMP(), m_status.GetMaxMP(),
					m_status.GetSP(), m_status.GetMaxSP()
				);

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

			// UI�Ƀv���C���[�̃X�e�[�^�X��n��
			m_playerBattleStatusUI->SetUIPlayerStatus(
				m_status.GetHP(), m_status.GetMaxHP(),
				m_status.GetMP(), m_status.GetMaxMP(),
				m_status.GetSP(), m_status.GetMaxSP()
			);

#ifdef _DEBUG
			//�v���C���[��HP��\���B

			//size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			//StringCbPrintf(m_dispText, dispTextSize, L"Level = %d , Exp = %d", m_status.GetLevel(), m_status.GetExp());
			//m_fontRenderer->SetText(m_dispText);
#endif
		}

		void CPlayer::ApplyDamage(float damage, float power, bool canGuard) {

			//��e���͔�e���Ȃ��B
			if (m_action.GetState() == EnPlayerState::enDamage) {

				//�I���B
				return;
			}

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
					m_input.InputDisable();

					//���Ђ�񂾂̂ŁA���ȏ�̂Ђ�݂͖����Ƃ���B
					while (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

						//�Ђ�ݒl�����Z�B
						m_status.SubWinceValue(m_status.GetWinceDelimiter());
					}
				}
			}

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
			//modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFilePath = nsHumans::g_kNameToModelFilePath.at("Player1");
			//modelInitData.textureRootPath = kPlayerModelTextureRootPath;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationZ(nsMath::YM_PI);
			modelInitData.SetFlags(EnModelInitDataFlags::enCullingOff);
			modelInitData.SetFlags(EnModelInitDataFlags::enLoadingAsynchronous);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterAnimationBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterTextureBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enShadowCaster);


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


		void CPlayer::InitAfterLoadModel()
		{
			if (m_modelRenderer->IsLoadingAsynchronous())
			{
				return;
			}

			//�A�j���[�V�����Ɏg�p���郂�f����`����B
			m_animation.SetPlayerModelAndAnimEvent(m_modelRenderer);

			//����Ǘ��N���X���������B
			m_weaponManager.Init(this, m_modelRenderer, &m_action);

			//�X�e�[�^�X���������B
			m_status.Init(m_weaponManager.GetWeaponPointer(), m_armor, GetPassiveSkillManager(), GetFeatureManager());

			//���̓N���X���������B
			m_input.Init(this, &m_action, &m_animation);

			//�A�N�V�����N���X���������B
			m_action.Init(m_position, m_rotation, &m_status, GetFeatureManager(), &m_animation);

			//�����蔻����������B
			m_collider.Init(this);

			// UI�̏���
			m_playerBattleStatusUI = NewGO<nsUI::CPlayerBattleStatusUI>();
			m_playerBattleStatusUI->LoadLevel();

			m_skillIconUI = NewGO<nsUI::CSkillIconUI>();
			m_skillIconUI->LoadLevel();

			m_itemUI = NewGO<nsUI::CItemUI>();
			m_itemUI->LoadLevel();


			//�v���C���[�Ǘ��N���X���������B
			CPlayerManager::GetInstance()->Init(this);

			m_menuManager = NewGO<nsUI::CMenuManager>();

			//�f�[�^�����[�h�B
			CUserData userData;
			userData.Load();

			m_isInited = true;

			return;
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

		////////////////////////////////////////////////////////////
		// UI
		////////////////////////////////////////////////////////////

		void CPlayer::ChangeFromSkillToItemUI()
		{
			m_skillIconUI->DeactiveDrawing();
			m_itemUI->ActiveDrawing();
		}

		void CPlayer::ChangeFromItemToSkillUI()
		{
			m_itemUI->DeactiveDrawing();
			m_skillIconUI->ActiveDrawing();
		}

		void CPlayer::MoveNextItemUI()
		{
			m_itemUI->MoveNextItemUI();
		}

		void CPlayer::MoveBackItemUI()
		{
			m_itemUI->MoveBackItemUI();
		}
	}
}

