#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Monster.h"
#include "MonsterList.h"
#include "../Item/MaterialItemList.h"

#include "../UI/Battle/Enemy/EnemyBattleStatusUI.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr const char* const kMonsterModelTextureRootPath = "monster";	//�����X�^�[���f���̃e�N�X�`���̃p�X
			constexpr int kDropMin = 1;	//�h���b�v�Œ�m��
			constexpr int kDropMax = 100;//�h���b�v�ő�m��
			constexpr int kNormalItemDropPer = 80;//�m�[�}���A�C�e���̃h���b�v��(��)
			constexpr int kRareItemDropPer = 30;//���A�A�C�e���̃h���b�v��(��)
		}

		const char* const CMonster::m_kObjName_Monster = "Monster";

		bool CMonster::StartSub() {

			return true;
		}

		void CMonster::OnDestroySub() {

			//�A�j���[�V������j���B
			m_animation.Release();

			//�R���C�_�[��j���B
			m_collider.Release();

			//AI�R���g���[���[��j���B
			m_AIContoller.Release();

			// UI��j��
			DeleteGO(m_enemyBattleStatusUI);
		}

		void CMonster::UpdateActor(float deltaTime) {

			if (m_isInited != true)
			{
				InitAfterLoadModel();
				return;
			}


			// UI�̏���
			m_enemyBattleStatusUI->SetUIEnemyStatus(
				m_status.GetHP(), m_status.GetMaxHP(), 0.0f
			);
			m_enemyBattleStatusUI->SetUIEnemyPosition(m_position);

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

			m_initData = monsterInfo;

			//�����X�^�[���f���𐶐��B
			CreateMonsterModel(m_initData);


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
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterAnimationBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterTextureBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enLoadingAsynchronous);
			modelInitData.SetFlags(EnModelInitDataFlags::enShadowCaster);

			
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

		void CMonster::InitAfterLoadModel()
		{
			if (m_modelRenderer->IsLoadingAsynchronous())
			{
				return;
			}

			//���O��ݒ�B
			m_name = m_initData.name;

			//�l���o���l�ʂ�ݒ�B
			m_dropExp = m_initData.dropExp;

			//�h���b�v�A�C�e���̃��X�g��ݒ�B
			m_dropItemList = m_initData.dropMaterialItemList;

			//�X�e�[�^�X���������B
			m_status.Init(m_name);

			//������ݒ�B
			m_status.SetAttribute(m_initData.attribute);

			//�A�j���[�V�����C�x���g���������B
			m_animation.InitAnimationEvent(this, &m_AIContoller);

			//�A�j���[�V�������������B
			m_animation.Init(
				m_modelRenderer,
				m_initData.animDataList,
				m_initData.animationFilePath
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

			m_isInited = true;

			return;
		}


		CStatus* CMonster::GetStatus() {

			//�X�e�[�^�X���擾�B
			return &m_status;
		}

		bool CMonster::CheckDrop(const std::string& dropItemName) {

			//�f�ރA�C�e�����X�g�N���X�̃C���X�^���X���擾�B
			auto materialItemListInstance = nsItem::CMaterialItemList::GetInstance();

			//�f�ރA�C�e�������擾�B
			nsItem::SMaterialItemInfo materialItem = materialItemListInstance->GetMaterialItemInfo(dropItemName);

			//���I�B
			int result = Random()->GetRangeInt(kDropMin, kDropMax);

			//���ʂ����^�[���B
			if (materialItem.rank == "Normal" && result <= kNormalItemDropPer
				|| materialItem.rank == "Rare" && result <= kRareItemDropPer
				){

				//�����B
				return true;
			}
			else {
				//���s�B
				return false;
			}
		}
	}
}
