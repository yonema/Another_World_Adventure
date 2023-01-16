#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;

	namespace nsMonster {

		namespace nsMonsterAI {

			//�u���b�N�{�[�h
			//AI�Ŏg�p��������L������B
			struct SMonsterAIBlackboard : nsUtils::SNoncopyable
			{
				IGameActor* m_gameActor = nullptr;	//�Q�[���A�N�^�[�̃|�C���^
				CVector3 m_targetPosition = CVector3::Zero();		//�ڕW�̍��W
				float m_waitTimer = 0.0f;		//�ҋ@����
			};
		}
	}
}