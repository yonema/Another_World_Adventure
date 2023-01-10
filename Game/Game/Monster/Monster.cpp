#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Monster.h"
#include "MonsterList.h"

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
		}

		void CMonster::UpdateActor(float deltaTime) {

			//�X�e�[�g�̕ύX�󋵂��������B
			m_isChangeState = false;

			//�A�j���[�V�������X�V�B
			//m_animation.Update(m_isChangeState, m_state);
		}

		void CMonster::Create(const SMonsterInitData& monsterInfo) {

			//�����X�^�[���f���𐶐��B
			CreateMonsterModel(monsterInfo);

			//���O��ݒ�B
			m_name = monsterInfo.name.c_str();

			//�A�j���[�V�������������B
			m_animation.Init(
				m_modelRenderer,
				monsterInfo.animDataList,
				monsterInfo.animationFilePath
			);

#ifdef _DEBUG
			//���ɑҋ@��Ԃɐݒ�B
			SetState(EnMonsterState::enIdle);
#endif
		}

		void CMonster::ApplyDamage(float damage, float power, bool canGuard) {


		}

		void CMonster::CreateMonsterModel(const SMonsterInitData& monsterInfo) {

			//�����X�^�[���f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�����X�^�[���f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = monsterInfo.modelFilePath.c_str();
			modelInitData.textureRootPath = kMonsterModelTextureRootPath;
			modelInitData.vertexBias.AddRotationX(-(nsMath::YM_PIDIV2));
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);
			
			//�A�j���[�V�����̐����擾�B
			const int animNum = monsterInfo.animationFilePath.size();

			//�A�j���[�V�����̃t�@�C���p�X�̔z����`�B
			std::vector<const char*> animNumVec;

			//�A�j���[�V�����̐������񂵂ăt�@�C���p�X���i�[�B
			for (int animIndex = 0; animIndex < animNum; animIndex++) {
			
				//�A�j���[�V�����̃t�@�C���p�X���擾�B
				animNumVec.emplace_back(monsterInfo.animationFilePath[animIndex].c_str());
			}
			
			//�A�j���[�V�����̃f�[�^�𐶐��B
			SAnimationInitData* animData = new SAnimationInitData(
				static_cast<unsigned int>(animNum),
				animNumVec.data()
			);

			//�A�j���[�V�����̃f�[�^��ݒ�B
			modelInitData.animInitData = animData;
			
			//�����X�^�[���f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CStatus* CMonster::GetStatus() {

			//�X�e�[�^�X���擾�B
			return &m_status;
		}

		nsWeapon::CWeapon* CMonster::GetWeapon() {

			//������擾�B
			return m_weapon;
		}

		nsArmor::CArmor* CMonster::GetArmor() {

			//�h����擾�B
			return m_armor;
		}
	}
}
