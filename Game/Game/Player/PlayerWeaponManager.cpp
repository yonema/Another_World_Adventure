#include "YonemaEnginePreCompile.h"
#include "PlayerWeaponManager.h"
#include "PlayerAction.h"
#include "Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const char* const kPlayerWeaponBaseBoneID = "J_Bip_R_Hand";	//プレイヤーの武器持ち場所
			constexpr float kEffectAddPosition = 10.0f;		//エフェクト発生場所
			constexpr float kEffectScale = 2.0f;		//エフェクトサイズ
		}

		void CPlayerWeaponManager::Init(const CPlayer* player, const CModelRenderer* playerModel, const CPlayerAction* action) {

			//プレイヤーを格納。
			m_player = player;

			//プレイヤーモデルを取得。
			m_playerModel = playerModel;

			//プレイヤーアクションを取得。
			m_playerAction = action;

			//モデルが入っていないなら。
			if (m_playerModel == nullptr) {

				//エラー出力。
				nsGameWindow::MessageBoxError(L"CPlayerWeaponManager : モデルの取得に失敗しました。");
				return;
			}

			//武器を持たせるボーンのIDを取得。
			m_weaponBaseBoneID = m_playerModel->FindBoneId(kPlayerWeaponBaseBoneID);

			//UINTの最大値が返ってきたら。
			if (m_weaponBaseBoneID == UINT_MAX) {

				//ボーンのIDが入っていないので、エラー出力。
				nsGameWindow::MessageBoxError(L"CPlayerWeaponManager : ボーンの取得に失敗しました。");
				return;
			}
		}

		void CPlayerWeaponManager::Update() {

			//街中にいるなら。
			if (m_player->IsInTown()) {

				//武器を無効化。
				m_weapon->GetModelRenderer()->ModelDeactivate();

				//終了。
				return;
			}
			else {

				//武器を有効化。
				m_weapon->GetModelRenderer()->ModelActivate();
			}

			//スキル使用中じゃなく、エフェクトが入っていたら。
			if (m_playerAction->GetState() != EnPlayerState::enUseActiveSkill
				&& m_mainEffect != nullptr
				) {

				//エフェクトを破棄。
				m_mainEffect->Stop();
				DeleteGO(m_mainEffect);
				m_mainEffect = nullptr;
			}

			//武器情報が入っていないなら。
			if (m_weapon == nullptr) {

				//早期リターン。
				return;
			}

			//ボーン行列を取得。
			const auto& mBone = m_playerModel->GetBoneMatixWS(m_weaponBaseBoneID);

			// 行列から座標、回転、拡大率を計算して格納。
			nsMath::CVector3 bonePos;
			nsMath::CQuaternion boneRot;
			nsMath::CVector3 boneScale;
			nsMath::CalcTRSFromMatrix(bonePos, boneRot, boneScale, mBone);

			//武器のtransformを設定。
			m_weapon->SetPosition(bonePos);
			m_weapon->SetRotation(boneRot);
			m_weapon->SetScale(boneScale);

			//エフェクトが入っているなら。
			if (m_mainEffect != nullptr) {

				//エフェクトを更新。
				UpdateEffect();
			}
		}

		void CPlayerWeaponManager::ChangeWeapon(nsWeapon::CWeapon* weapon) {

			//既に武器情報が入っていたら。
			if (m_weapon != nullptr) {

				//武器を破棄。
				m_weapon->Release();
				m_weapon = nullptr;
			}

			//武器を設定。
			m_weapon = weapon;
		}

		void CPlayerWeaponManager::CreateEffect(const std::string& effectFilePath) {

			//メインエフェクトを生成。
			m_mainEffect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Weapon/";
			mainEffectFilePath += effectFilePath;
			mainEffectFilePath += ".efkefc";

			//初期化。
			m_mainEffect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//更新。
			UpdateEffect();

			//エフェクトを再生。
			m_mainEffect->Play();
		}

		void CPlayerWeaponManager::UpdateEffect() {

			//エフェクト発生場所を取得。
			CVector3 weaponBasePosition = CVector3::Down();

			const CQuaternion& rot = m_weapon->GetModelRenderer()->GetRotation();

			rot.Apply(weaponBasePosition);

			weaponBasePosition *= kEffectAddPosition;

			//エフェクトの座標と回転を設定。
			m_mainEffect->SetPosition(m_weapon->GetPosition() + weaponBasePosition);
			m_mainEffect->SetRotation(m_weapon->GetRotation());
			m_mainEffect->SetScale(kEffectScale);
		}
	}
}