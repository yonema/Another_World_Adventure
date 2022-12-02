#pragma once

namespace nsAWA {

	/**
	 * @brief �����X�^�[�̃X�e�[�g�ƃ��X�g
	*/
	namespace nsMonster {

		//�����X�^�[�̃X�e�[�g
		enum class EnMonsterState {

			enIdle,		//�ҋ@

			enNum,		//�X�e�[�g�̐�
			enNone = -1	//�ݒ�Ȃ�
		};

		//�����X�^�[�̃��X�g
		enum class EnMonsterList {

			enGiyara,		//�M����

			enNum,			//�����X�^�[�̎�ނ̐�
			enNone = -1		//�ݒ�Ȃ�
		};

	}

	/**
	 * @brief �M����
	*/
	namespace nsMonster {

		//�M�����̃A�j���[�V����
		enum class EnGiyaraAnimation {

			enIdle,			//�ҋ@

			enNum,			//�A�j���[�V�����̐�
			enNone = -1		//�ݒ�Ȃ�
		};

		//�M�����̃A�j���[�V�����̃t�@�C���p�X
		constexpr const char* kGiyaraAnimFilePaths[static_cast<int>(EnGiyaraAnimation::enNum)] = {

			"Assets/Animations/Monster/Giyara/Giyara_Idle.fbx",
		};

		int GetGiyaraAnimationIndex(EnMonsterState state);
	}

	/**
	 * @brief ���ʂ̃Q�b�^�[
	*/
	namespace nsMonster {

		int GetAnimationNum(EnMonsterList monster);

		const char* GetAnimationFilePath(EnMonsterList monster, int animIndex);

		int GetAnimationIndex(EnMonsterList monster, EnMonsterState state);
	}
}