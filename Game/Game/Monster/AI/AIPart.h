#pragma once
#include "MonsterAIBlackboard.h"
#include "MonsterAIController.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//AIの部品クラス
			class CAIPart : nsUtils::SNoncopyable
			{
			public:
				virtual bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) = 0;

				void Release();

				void AddAIPart(CAIPart* AIPart) {

					//AI部品をリストに追加。
					m_AIPartList.emplace_back(AIPart);
				}

				

			public:
				void SetName(const std::string& name) {

					//名前を設定。
					m_name = name;
				}

				const std::string& GetName()const {

					//名前をリターン。
					return m_name;
				}

				void SetPartInfo(const std::vector<std::string>& info) {

					//情報を追加。
					m_partInfo = info;
				}

				const std::vector<std::string>& GetPartInfo()const {

					//情報を取得。
					return m_partInfo;
				}

				void SetAIController(CMonsterAIController* AIcontroller) {

					//AIコントローラーを設定。
					m_AIController = AIcontroller;
				}
			protected:
				std::string m_name = "NoName";			//名前
				std::list<CAIPart*> m_AIPartList;		//AI部品のリスト
				std::vector<std::string> m_partInfo;	//情報
				CMonsterAIController* m_AIController = nullptr;	//AIコントローラー
			};
		}
	}
}