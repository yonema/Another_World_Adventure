#pragma once

namespace nsAWA {

	//エイリアス宣言
	namespace nsFeature {

		class CFeature;
	}

	namespace nsItem {

		//アイテムクラス
		class CItem : public IGameObject
		{
		public:

			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			virtual void Use() = 0;

			void AddFeature(nsFeature::CFeature* feature) {

				//効果をリストに追加。
				m_featureList.emplace_back(feature);
			}

		protected:
			void ExecuteFeature();

		public:
			void SetName(const char* name) {

				//名前を設定。
				m_name = name;
			}

			const char* GetName()const {

				//名前を取得。
				return m_name;
			}

		private:
			const char* m_name = nullptr;	//名前
			CModelRenderer* m_itemModel = nullptr;	//モデル
			CQuaternion m_rotation = CQuaternion::Identity();	//モデルの回転

			std::list<nsFeature::CFeature*> m_featureList;	//効果のリスト
			float m_getValidTimer = 0.0f;	//取得有効時間タイマー
			bool m_isGet = false;	//取得されている？
		};
	}
}

