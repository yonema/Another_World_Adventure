#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Monster.h"
#include "MonsterList.h"

#include "../UI/Battle/Enemy/EnemyBattleStatusUI.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr const char* const kMonsterModelTextureRootPath = "monster";	//モンスターモデルのテクスチャのパス
		}

		const char* const CMonster::m_kObjName_Monster = "Monster";

		bool CMonster::StartSub() {

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

			// UIの処理
			m_enemyBattleStatusUI->SetUIEnemyStatus(
				m_status.GetHP(), m_status.GetMaxHP(), 0.0f
			);
			// nsGraphics::CCamera::CalcScreenPositionFromWorldPosition()
			m_enemyBattleStatusUI->SetUIEnemyPosition(MainCamera()->CalcScreenPositionFromWorldPosition(m_position));
			


			//死んでいるなら。
			if (IsDeath()) {

				//死亡状態に。
				SetState(EnMonsterState::enDeath);

				//アニメーションを更新。
				m_animation.Update(m_isChangeState, m_state);

				//ステートの変更状況を初期化。
				m_isChangeState = false;

				//コライダーを破棄。
				if (!m_collider.IsReleased()) {

					m_collider.Release();
				}

				//これ以上は何もせず終了。
				return;
			}

			//AIコントローラーを更新。
			m_AIContoller.Update(deltaTime);

			//コライダーを更新。
			m_collider.Update();

			//アニメーションを更新。
			m_animation.Update(m_isChangeState, m_state);		

			//ステートの変更状況を初期化。
			m_isChangeState = false;
		}

		void CMonster::Create(const SMonsterInitData& monsterInfo) {

			//モンスターモデルを生成。
			CreateMonsterModel(monsterInfo);

			//名前を設定。
			m_name = monsterInfo.name;

			//ステータスを初期化。
			m_status.Init(m_name);

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

			//待機状態に設定。
			SetState(EnMonsterState::enIdle);

			// UIの処理
			m_enemyBattleStatusUI = NewGO<nsUI::CEnemyBattleStatusUI>();
			m_enemyBattleStatusUI->LoadLevel();
		}

		void CMonster::ApplyDamage(float damage, float power, bool canGuard) {

			//ダメージをくらう。
			m_status.DamageHP(damage);

			//ひるみ値を加算。
			m_status.AddWinceValue(damage);

			//ひるみ値がひるみ値の区切りを超えていたら。
			if (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

				//ダメージ状態に設定。
				SetState(EnMonsterState::enDamage);

				//クールタイムをONに設定。
				m_AIContoller.CoolTimeOn();

				//一回ひるんだので、二回以上のひるみは無効とする。
				while (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

					//ひるみ値を減算。
					m_status.SubWinceValue(m_status.GetWinceDelimiter());
				}
			}

			//プレイヤーを発見。
			m_AIContoller.FindPlayer();
		}

		void CMonster::CreateMonsterModel(const SMonsterInitData& monsterInfo) {

			//モンスターモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//モンスターモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = monsterInfo.modelFilePath.c_str();
			modelInitData.textureRootPath = kMonsterModelTextureRootPath;
			
			//アニメーションの数を取得。
			const int animNum = static_cast<int>(monsterInfo.animationFilePath.size());

			//アニメーションのファイルパスの配列を定義。
			std::vector<const char*> animNumVec;

			//アニメーションの数だけ回してファイルパスを格納。
			for (int animIndex = 0; animIndex < animNum; animIndex++) {
			
				//アニメーションのファイルパスを取得。
				animNumVec.emplace_back(monsterInfo.animationFilePath[animIndex].c_str());
			}
		

			//アニメーションのデータを設定。
			modelInitData.animInitData.Init(
				static_cast<unsigned int>(animNum),
				animNumVec.data()
			);
			
			//モンスターモデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CStatus* CMonster::GetStatus() {

			//ステータスを取得。
			return &m_status;
		}
	}
}
