#include "MonsterList.h"

namespace nsAWA {

	//�M����
	namespace nsMonster {

		int GetGiyaraAnimationIndex(EnMonsterState state) {

			//�A�j���[�V������index���`�B
			EnGiyaraAnimation animIndex = EnGiyaraAnimation::enNone;

			//�X�e�[�g����Ή�����A�j���[�V������index���擾�B
			switch (state) {

				//�ҋ@
			case EnMonsterState::enIdle:

				//�ҋ@�A�j���[�V������ݒ�B
				animIndex = EnGiyaraAnimation::enIdle;
				break;

				//����ȊO
			default:
				//�ݒ�Ȃ��ɐݒ�B
				animIndex = EnGiyaraAnimation::enNone;
				break;
			}

			//int�^�ɕϊ�����index�����^�[���B
			return static_cast<int>(animIndex);
		}
	}

	//���ʂ̃Q�b�^�[
	namespace nsMonster {

		int GetAnimationNum(EnMonsterList monster) {

			//�����X�^�[�̎�ނ���K�؂ȃA�j���[�V�����������^�[���B
			switch (monster) {

			case EnMonsterList::enGiyara:
				return static_cast<int>(EnGiyaraAnimation::enNum);
			default:

				nsGameWindow::MessageBoxError(L"�����X�^�[�̎w�肪����������܂���B");
				return -1;
			}
		}

		const char* GetAnimationFilePath(EnMonsterList monster, int animIndex) {

			//�����X�^�[�̎�ނ���K�؂ȃt�@�C���p�X�����^�[���B
			switch (monster) {

				//�M����
			case EnMonsterList::enGiyara:

				//�M�����̃A�j���[�V�����̃t�@�C���p�X�����^�[���B
				return kGiyaraAnimFilePaths[animIndex];

			default:

				nsGameWindow::MessageBoxError(L"�����X�^�[�̎w�肪����������܂���B");
				return nullptr;
			}
		}

		int GetAnimationIndex(EnMonsterList monster, EnMonsterState state) {

			//�����X�^�[�̎�ނƃX�e�[�g���炩��K�؂ȃA�j���[�V���������^�[���B
			switch (monster) {

				//�M����
			case EnMonsterList::enGiyara:

				//�M�����̑Ή��A�j���[�V���������^�[���B
				return GetGiyaraAnimationIndex(state);

				//����ȊO
			default:

				nsGameWindow::MessageBoxError(L"�����X�^�[�̎w�肪����������܂���B");
				return -1;
			}
		}
	}
}