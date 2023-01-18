#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Monster.h"
#include "MonsterList.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr const char* const kMonsterModelTextureRootPath = "monster";	//モンスターモデルのテクスチャのパス
		}

		const char* const CMonster::m_kObjName_Monster = "Monster";

		bool CMonster::StartSub() {

			//ステータスを初期化。
			m_status.Init();

			return true;
		}

		void CMonster::OnDestroySub() {

			//モンスターモデルを破棄。
			DeleteGO(m_modelRenderer);

			//アニメーションを破棄。
			m_animation.Release();

			//コライダーを破棄。
			m_collider.Release();

			//AIコントローラーを破棄。
			m_AIContoller.Release();
		}

		void CMonster::UpdateActor(float deltaTime) {

			//ステートの変更状況を初期化。
			m_isChangeState = false;

			//死んでいるなら。
			if (IsDeath()) {

				//死亡状態に。
				SetState(EnMonsterState::enDeath);

				//アニメーションを更新。
				m_animation.Update(m_isChangeState, m_state);

				//これ以上は何もせず終了。
				return;
			}

			//AIコントローラーを更新。
			m_AIContoller.Update(deltaTime);

			//コライダーを更新。
			m_collider.Update();

			//アニメーションを更新。
			m_animation.Update(m_isChangeState, m_state);

			//座標を設定。
			m_modelRenderer->SetPosition(m_position);

			//回転を設定。
			m_modelRenderer->SetRotation(m_rotation);
		}

		void CMonster::Create(const SMonsterInitData& monsterInfo) {

			//モンスターモデルを生成。
			CreateMonsterModel(monsterInfo);

			//名前を設定。
			m_name = monsterInfo.name.c_str();

			//アニメーションイベントを初期化。
			m_animation.InitAnimationEvent(this, &m_AIContoller);

			//アニメーションを初期化。
			m_animation.Init(
				m_modelRenderer,
				monsterInfo.animDataList,
				monsterInfo.animationFilePath
			);

			//AIコントローラーを初期化。
			m_AIContoller.Init(this);

			//当たり判定を初期化。
			m_collider.Init(this);

#ifdef _DEBUG
			//仮に待機状態に設定。
			SetState(EnMonsterState::enIdle);
#endif
		}

		void CMonster::ApplyDamage(float damage, float power, bool canGuard) {

			//ダメージをくらう。
			m_status.DamageHP(damage);
		}

		void CMonster::CreateMonsterModel(const SMonsterInitData& monsterInfo) {

			//モンスターモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//モンスターモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = monsterInfo.modelFilePath.c_str();
			modelInitData.textureRootPath = kMonsterModelTextureRootPath;
			modelInitData.vertexBias.AddRotationX(-(nsMath::YM_PIDIV2));
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);
			
			//アニメーションの数を取得。
			const int animNum = static_cast<int>(monsterInfo.animationFilePath.size());

			//アニメーションのファイルパスの配列を定義。
			std::vector<const char*> animNumVec;

			//アニメーションの数だけ回してファイルパスを格納。
			for (int animIndex = 0; animIndex < animNum; animIndex++) {
			
				//アニメーションのファイルパスを取得。
				animNumVec.emplace_back(monsterInfo.animationFilePath[animIndex].c_str());
			}
			
			//アニメーションのデータを生成。
			SAnimationInitData* animData = new SAnimationInitData(
				static_cast<unsigned int>(animNum),
				animNumVec.data()
			);

			//アニメーションのデータを設定。
			modelInitData.animInitData = animData;
			
			//モンスターモデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CStatus* CMonster::GetStatus() {

			//ステータスを取得。
			return &m_status;
		}

		nsWeapon::CWeapon* CMonster::GetWeapon() {

			//武器を取得。
			return m_weapon;
		}

		nsArmor::CArmor* CMonster::GetArmor() {

			//防具を取得。
			return m_armor;
		}
	}
}
