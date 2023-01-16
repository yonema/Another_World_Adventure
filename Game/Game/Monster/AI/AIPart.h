#pragma once
#include "MonsterAIBlackboard.h"
#include "MonsterAIController.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//AI�̕��i�N���X
			class CAIPart : nsUtils::SNoncopyable
			{
			public:
				virtual bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) = 0;

				void Release();

				void AddAIPart(CAIPart* AIPart) {

					//AI���i�����X�g�ɒǉ��B
					m_AIPartList.emplace_back(AIPart);
				}

				

			public:
				void SetName(const std::string& name) {

					//���O��ݒ�B
					m_name = name;
				}

				const std::string& GetName()const {

					//���O�����^�[���B
					return m_name;
				}

				void SetPartInfo(const std::vector<std::string>& info) {

					//����ǉ��B
					m_partInfo = info;
				}

				const std::vector<std::string>& GetPartInfo()const {

					//�����擾�B
					return m_partInfo;
				}

				void SetAIController(CMonsterAIController* AIcontroller) {

					//AI�R���g���[���[��ݒ�B
					m_AIController = AIcontroller;
				}
			protected:
				std::string m_name = "NoName";			//���O
				std::list<CAIPart*> m_AIPartList;		//AI���i�̃��X�g
				std::vector<std::string> m_partInfo;	//���
				CMonsterAIController* m_AIController = nullptr;	//AI�R���g���[���[
			};
		}
	}
}