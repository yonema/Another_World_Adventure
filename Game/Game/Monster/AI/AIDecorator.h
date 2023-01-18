#pragma once

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//�O���錾
			struct SMonsterAIBlackboard;

			//AI�̃f�R���[�^�[
			//�򉻔ŁBbool�̃|�C���^�ϐ��������A�t���O�̎Q�Ƃ��󂯎���ĕ]������
			class CAIDecorator : nsUtils::SNoncopyable
			{
			public:
				void Init(bool* flag);

				void Reverse() {

					//�t�̕]��������B
					m_reverse = true;
				}

				void Release();

				bool Evaluate()const {

					//�t���O����]���B
					if (m_reverse) {

						return *m_falgRef ? false : true;
					}
					else {

						return *m_falgRef;
					}
				}

			private:
				bool* m_falgRef = nullptr;	//���炩�̃t���O
				bool m_reverse = false;		//�t�̕]��������H
			};

			//�f�R���[�^�[�����N���X
			class CAIDecoratorBuilder : nsUtils::SNoncopyable {

			public:
				CAIDecorator* CreateDecorator(const std::string& flagStr, SMonsterAIBlackboard* blackboard);
			};
		}
	}
}

