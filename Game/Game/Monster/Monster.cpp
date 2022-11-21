#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Monster.h"

namespace nsAWA {

	namespace nsMonster {

		const char* const CMonster::m_kObjName_Monster = "Monster";

		bool CMonster::Start() {

			return true;
		}

		void CMonster::OnDestroy() {

			//�����X�^�[���f����j���B
			DeleteGO(m_modelRenderer);
		}

		void CMonster::UpdateActor(float deltaTime) {


		}

		void CMonster::Create(const SMonsterInfo& monsterInfo) {

			//�����X�^�[���f���𐶐��B
			CreateMonsterModel(monsterInfo);

			//���O��ݒ�B
			m_name = monsterInfo.name;
		}

		void CMonster::ApplyDamage(float power, bool canGuard) {


		}

		void CMonster::CreateMonsterModel(const SMonsterInfo& monsterInfo) {

			//�����X�^�[���f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�����X�^�[���f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = monsterInfo.modelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.AddRotationX(-(nsMath::YM_PIDIV2));
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);

			//�����X�^�[���f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CStatus* CMonster::GetStatus() {

			//�X�e�[�^�X���󂯎��B
			return &m_status;
		}

		nsWeapon::CWeapon* CMonster::GetWeapon() {

			//������󂯎��B
			return m_weapon;
		}

		nsArmor::CArmor* CMonster::GetArmor() {

			//�h����󂯎��B
			return m_armor;
		}
	}
}
