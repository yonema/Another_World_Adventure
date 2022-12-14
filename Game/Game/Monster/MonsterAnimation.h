#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsMonster {

		enum class EnMonsterState;
		enum class EnMonsterList;
	}

	namespace nsMonster {

		//エイリアス宣言
		using AnimationEventDataStr = std::list<std::vector<std::string>>;

		//アニメーションイベントデータ
		struct SAnimationEventData {

			std::string eventName = "NoName";					//イベント名
			bool hasEventMaterial = false;						//イベントに必要な材料がある？
			AnimationEventDataStr eventMaterial;				//イベント材料
		};

		//アニメーションデータ
		struct SAnimData {

			std::string animName = "NoName";	//アニメーション名
			int animNum = -1;					//アニメーション番号
			float speed = 0.0f;							//速度
			bool isLoopAnim = false;					//ループする？
			std::vector<SAnimationEventData> animationEvent;			//アニメーションイベント
		};

		//モンスターアニメーションクラス
		class CMonsterAnimation : nsUtils::SNoncopyable
		{
			
		public:
			void Init(
				CModelRenderer* monsterModel,
				const std::vector<SAnimData>& animDataList,
				const std::vector<std::string>& animFilePathArray
			);

			void Update(bool changeState, EnMonsterState state);

			void LoadAnimation(
				const std::string& monsterName,
				const wchar_t* monsterAnimationCSVFilePath,
				const wchar_t* monsterAnimationEventCSVFilePath
			);

		private:
			void PlayAnimation(EnMonsterState state);

			const SAnimData& GetAnimationData(EnMonsterState state)const;

		public:
			const std::vector<SAnimData>& GetAnimDataList()const {

				//アニメーションデータを取得。
				return m_animDataList;
			}

			const std::vector<std::string>& GetAnimFilePathArray()const {

				//アニメーションファイルパスを取得。
				return m_animFilePathArray;
			}

		private:
			CModelRenderer* m_monsterModel = nullptr;	//モンスターモデル
			std::vector<SAnimData> m_animDataList;	//アニメーションデータ
			std::vector<std::string> m_animFilePathArray;	//アニメーションのファイルパスの配列
		};
	}
}

