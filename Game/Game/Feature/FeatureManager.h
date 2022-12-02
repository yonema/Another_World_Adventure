#pragma once
namespace nsAWA {

	//前方宣言
	namespace nsFeature {

		class CFeature;
	}

	namespace nsFeature {

		//機能管理クラス
		class CFeatureManager : nsUtils::SNoncopyable
		{
		public:
			void AddStatusChanger(nsFeature::CFeature* statusChanger) {

				//ステータス変化を付与。
				m_feature.emplace_back(statusChanger);
			}

			void UpdateFeature(float deltaTime);

			bool IsParalysis()const {

				//麻痺状態かどうかリターンする。
				return m_isParalysis;
			}

			bool IsPoison()const {

				//毒状態かどうかリターンする。
				return m_isPoison;
			}

			bool CanUseActiveSkill();

		private:
			void UpdateFeatureState();
		private:
			std::list<nsFeature::CFeature*> m_feature;	//ステータスを変化させるもののリスト
			bool m_isPoison = false;		//毒状態？
			bool m_isParalysis = false;		//麻痺状態？
		};
	}
}

