#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;

	namespace nsMagic {

		//魔法クラスのベース
		class CMagicBase : public IGameObject
		{
		public:
			void SetOwner(IGameActor* owner) {

				//発動者を設定。
				m_owner = owner;
			}

			IGameActor* GetOwner()const {

				//発動者を取得。
				return m_owner;
			}

			void SetMagicName(const std::string& name) {

				//名前を設定。
				m_name = name;
			}

			const std::string& GetMagicName()const {

				//名前を取得。
				return m_name;
			}

			void SetPosition(const CVector3& position) {

				//座標を設定。
				m_position = position;
			}

			const CVector3& GetPosition()const {

				//座標を取得。
				return m_position;
			}

			void SetMoveDirection(const CVector3& moveDirection) {

				//飛んでいく方向を設定。
				m_moveDirection = moveDirection;
			}

			const CVector3& GetMoveDirection()const {

				//飛んでいく方向を取得。
				return m_moveDirection;
			}

			void SetFeatureList(std::list<std::vector<std::string>> featureList) {

				//効果のリストを設定。
				m_featureList = featureList;
			}

			const std::list<std::vector<std::string>>& GetFeatureList()const {

				//効果のリストを取得。
				return m_featureList;
			}

			void ExecuteFeature(IGameActor* target);

		private:
			std::string m_name = "NoName";	//名前
			CVector3 m_position = CVector3::Zero();	//座標
			CVector3 m_moveDirection = CVector3::Zero();//飛んでいく方向
			IGameActor* m_owner = nullptr;	//発動者
			std::list<std::vector<std::string>> m_featureList;		//効果のリスト
		};
	}
}