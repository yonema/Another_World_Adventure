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

			void SetMagicName(const std::string& name) {

				//名前を設定。
				m_name = name;
			}

			const std::string& GetMagicName()const {

				//名前を取得。
				return m_name;
			}

			virtual void SetPosition(const CVector3& position) = 0;

			virtual void SetMoveDirection(const CVector3& moveDirection) = 0;

			void SetFeatureList(std::list<std::vector<std::string>> featureList) {

				//効果のリストを設定。
				m_featureList = featureList;
			}

			void ExecuteFeature(IGameActor* target);

		private:
			std::string m_name = "NoName";	//名前
			IGameActor* m_owner = nullptr;	//発動者
			std::list<std::vector<std::string>> m_featureList;		//効果のリスト
		};
	}
}