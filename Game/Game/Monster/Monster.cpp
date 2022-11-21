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

			//モンスターモデルを破棄。
			DeleteGO(m_modelRenderer);
		}

		void CMonster::UpdateActor(float deltaTime) {


		}

		void CMonster::Create(const SMonsterInfo& monsterInfo) {

			//モンスターモデルを生成。
			CreateMonsterModel(monsterInfo);

			//名前を設定。
			m_name = monsterInfo.name;
		}

		void CMonster::ApplyDamage(float power, bool canGuard) {


		}

		void CMonster::CreateMonsterModel(const SMonsterInfo& monsterInfo) {

			//モンスターモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//モンスターモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = monsterInfo.modelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.AddRotationX(-(nsMath::YM_PIDIV2));
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);

			//モンスターモデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CStatus* CMonster::GetStatus() {

			//ステータスを受け取る。
			return &m_status;
		}

		nsWeapon::CWeapon* CMonster::GetWeapon() {

			//武器を受け取る。
			return m_weapon;
		}

		nsArmor::CArmor* CMonster::GetArmor() {

			//防具を受け取る。
			return m_armor;
		}
	}
}
