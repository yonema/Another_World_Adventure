#pragma once
#include "MonsterAIBlackboard.h"

namespace nsAWA {

	namespace nsMonster {

		//�O���錾
		class CMonster;
		enum class EnMonsterState;
		namespace nsMonsterAI {

			class CAIPart;
		}

		namespace nsMonsterAI {

			//�G�C���A�X�錾
			using AIPartsDataStr = std::list<std::vector<std::string>>;

			//�����X�^�[AI�R���g���[���[�N���X
			class CMonsterAIController : nsUtils::SNoncopyable
			{
			public:
				void Init(CMonster* owner);

				void Release();

				CAIPart* CreateAIPart(AIPartsDataStr& AIPartsData);

				void Update(float deltaTime);

			private:
				void UpdateForwardDirection();

			public:
				void SetPosition(const CVector3& position);

				const CVector3& GetPosition()const;

				void SetRotation(const CQuaternion& rotation);

				const CQuaternion& GetRotation()const;

				const CVector3& GetForwardDirection()const;

				float GetDeltaTimeRef()const {

					//�f���^�^�C�����擾�B
					return m_deltaTimeRef;
				}

				void SetState(const EnMonsterState& state);

				const EnMonsterState& GetState()const;

				void SetWaitNode(CAIPart* waitTask) {

					if (m_waitNode == nullptr) {

						//�ҋ@�^�X�N��ݒ�B
						m_waitNode = waitTask;
					}
				}

				void CoolTimeOn() {

					//�N�[���^�C�����ɂ���B
					m_isCoolTime = true;
				}

				void CoolTimeOff() {

					//�N�[���^�C����؂�B
					m_isCoolTime = false;
				}

				void FindPlayer() {

					//�v���C���[�𔭌��B
					m_blackboard.m_isfindingTarget = true;
				}

			private:
				CMonster* m_owner = nullptr;	//�����X�^�[�i���g�j�̃|�C���^
				SMonsterAIBlackboard m_blackboard;	//�u���b�N�{�[�h
				CAIPart* m_rootNode = nullptr;		//���[�g�m�[�h
				CAIPart* m_waitNode = nullptr;		//�ҋ@�^�X�N
				float m_deltaTimeRef = 0.0f;		//�f���^�^�C��
				bool m_isCoolTime = false;			//�N�[���^�C�����H
			};
		}
	}
}