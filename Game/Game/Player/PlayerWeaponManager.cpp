#include "YonemaEnginePreCompile.h"
#include "PlayerWeaponManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const char* const kPlayerWeaponBaseBoneID = "J_Bip_R_Hand";	//プレイヤーの武器持ち場所
		}

		void CPlayerWeaponManager::Init(const CModelRenderer* playerModel) {

			//プレイヤーモデルを取得。
			m_playerModel = playerModel;

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
		}

		void CPlayerWeaponManager::ChangeWeapon(const nsWeapon::SWeaponInfo& weaponInfo) {

			//既に武器情報が入っていたら。
			if (m_weapon != nullptr) {

				//武器を破棄。
				m_weapon->Release();
				m_weapon = nullptr;
			}

#ifdef _DEBUG
			//仮にモデルのファイルパスは自分で定義。
			const char* weaponModelFilePath = "Assets/Models/Sword.fbx";

			//武器構築クラスを生成。
			nsWeapon::CWeaponBuilder weaponBuilder;

			//武器情報を元に武器を生成。
			m_weapon = weaponBuilder.Create(weaponInfo, weaponModelFilePath);
#endif
		}
	}
}