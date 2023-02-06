#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Monster.h"
#include "MonsterList.h"

#include "../UI/Battle/Enemy/EnemyBattleStatusUI.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr const char* const kMonsterModelTextureRootPath = "monster";	//�����X�^�[���f���̃e�N�X�`���̃p�X
		}

		const char* const CMonster::m_kObjName_Monster = "Monster";

		bool CMonster::StartSub() {

			return true;
		}

		void CMonster::OnDestroySub() {

			//�����X�^�[���f����j���B
			DeleteGO(m_modelRenderer);

			//�A�j���[�V������j���B
			m_animation.Release();

			//�R���C�_�[��j���B
			m_collider.Release();

			//AI�R���g���[���[��j���B
			m_AIContoller.Release();
		}

		void CMonster::UpdateActor(float deltaTime) {

			// UI�̏���
			m_enemyBattleStatusUI->SetUIEnemyStatus(
				m_status.GetHP(), m_status.GetMaxHP(), 0.0f
			);
			// nsGraphics::CCamera::CalcScreenPositionFromWorldPosition()
			m_enemyBattleStatusUI->SetUIEnemyPosition(MainCamera()->CalcScreenPositionFromWorldPosition(m_position));
			


			//����ł���Ȃ�B
			if (IsDeath()) {

				//���S��ԂɁB
				SetState(EnMonsterState::enDeath);

				//�A�j���[�V�������X�V�B
				m_animation.Update(m_isChangeState, m_state);

				//�X�e�[�g�̕ύX�󋵂��������B
				m_isChangeState = false;

				//�R���C�_�[��j���B
				if (!m_collider.IsReleased()) {

					m_collider.Release();
				}

				//����ȏ�͉��������I���B
				return;
			}

			//AI�R���g���[���[���X�V�B
			m_AIContoller.Update(deltaTime);

			//�R���C�_�[���X�V�B
			m_collider.Update();

			//�A�j���[�V�������X�V�B
			m_animation.Update(m_isChangeState, m_state);		

			//�X�e�[�g�̕ύX�󋵂��������B
			m_isChangeState = false;
		}

		void CMonster::Create(const SMonsterInitData& monsterInfo) {

			//�����X�^�[���f���𐶐��B
			CreateMonsterModel(monsterInfo);

			//���O��ݒ�B
			m_name = monsterInfo.name;

			//�X�e�[�^�X���������B
			m_status.Init(m_name);

			//�A�j���[�V�����C�x���g���������B
			m_animation.InitAnimationEvent(this, &m_AIContoller);

			//�A�j���[�V�������������B
			m_animation.Init(
				m_modelRenderer,
				monsterInfo.animDataList,
				monsterInfo.animationFilePath
			);

			//AI�R���g���[���[���������B
			m_AIContoller.Init(this);

			//�����蔻����������B
			m_collider.Init(this);

			//�ҋ@��Ԃɐݒ�B
			SetState(EnMonsterState::enIdle);

			// UI�̏���
			m_enemyBattleStatusUI = NewGO<nsUI::CEnemyBattleStatusUI>();
			m_enemyBattleStatusUI->LoadLevel();
		}

		void CMonster::ApplyDamage(float damage, float power, bool canGuard) {

			//�_���[�W�����炤�B
			m_status.DamageHP(damage);

			//�Ђ�ݒl�����Z�B
			m_status.AddWinceValue(damage);

			//�Ђ�ݒl���Ђ�ݒl�̋�؂�𒴂��Ă�����B
			if (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

				//�_���[�W��Ԃɐݒ�B
				SetState(EnMonsterState::enDamage);

				//�N�[���^�C����ON�ɐݒ�B
				m_AIContoller.CoolTimeOn();

				//���Ђ�񂾂̂ŁA���ȏ�̂Ђ�݂͖����Ƃ���B
				while (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

					//�Ђ�ݒl�����Z�B
					m_status.SubWinceValue(m_status.GetWinceDelimiter());
				}
			}

			//�v���C���[�𔭌��B
			m_AIContoller.FindPlayer();
		}

		void CMonster::CreateMonsterModel(const SMonsterInitData& monsterInfo) {

			//�����X�^�[���f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�����X�^�[���f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = monsterInfo.modelFilePath.c_str();
			modelInitData.textureRootPath = kMonsterModelTextureRootPath;
			
			//�A�j���[�V�����̐����擾�B
			const int animNum = static_cast<int>(monsterInfo.animationFilePath.size());

			//�A�j���[�V�����̃t�@�C���p�X�̔z����`�B
			std::vector<const char*> animNumVec;

			//�A�j���[�V�����̐������񂵂ăt�@�C���p�X���i�[�B
			for (int animIndex = 0; animIndex < animNum; animIndex++) {
			
				//�A�j���[�V�����̃t�@�C���p�X���擾�B
				animNumVec.emplace_back(monsterInfo.animationFilePath[animIndex].c_str());
			}
		

			//�A�j���[�V�����̃f�[�^��ݒ�B
			modelInitData.animInitData.Init(
				static_cast<unsigned int>(animNum),
				animNumVec.data()
			);
			
			//�����X�^�[���f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CStatus* CMonster::GetStatus() {

			//�X�e�[�^�X���擾�B
			return &m_status;
		}
	}
}
