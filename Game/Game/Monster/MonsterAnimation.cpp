#include "YonemaEnginePreCompile.h"
#include "MonsterAnimation.h"
#include "MonsterList.h"

namespace nsAWA {

	namespace nsMonster {

		void CMonsterAnimation::Init(CModelRenderer* monsterModel, EnMonsterList monster) {

			//�����X�^�[�̃��f���̃|�C���^���󂯎��B
			m_monsterModel = monsterModel;

			//���̃����X�^�[�Ȃ̂��̏����󂯎��B
			m_monster = monster;
		}

		void CMonsterAnimation::Update(bool changeState, EnMonsterState state) {

			//�X�e�[�g�ɕύX����������B
			if (changeState) {

				//�X�e�[�g�ɑΉ�����A�j���[�V�������Đ��B
				PlayAnimation(state);
			}
		}

		void CMonsterAnimation::PlayAnimation(EnMonsterState state) {

			//�X�e�[�g����Ή��A�j���[�V������index���擾�B
			int animationIndex = GetAnimationIndex(m_monster, state);

			//�Ή�����A�j���[�V�������Ȃ��Ȃ�B
			if (animationIndex == -1) {

				//�Đ��ł��Ȃ��̂ő������^�[���B
				return;
			}
			else {

				//�Ή�����A�j���[�V�������Đ��B�i�܂��Đ��X�s�[�h�ƃ��[�v�t���O���ݒ�ł��Ȃ��B�������j
				m_monsterModel->PlayAnimation(animationIndex, 1.0f, true);
			}
		}
	}
}