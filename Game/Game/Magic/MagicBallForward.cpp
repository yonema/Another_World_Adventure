#include "YonemaEnginePreCompile.h"
#include "MagicBallForward.h"
#include "MagicBallOne.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr short kMagicBallNum = 3;	//���@�̐�
			constexpr float kInterval = 0.5f;	//���@�e�̊Ԋu�is�j
		}

		bool CMagicBallForward::Start() {

			//�^�C�}�[�̊Ԋu��ݒ�B
			m_magicIntervalTimer = kInterval;

			//���@�e�𐶐��B
			CreateMagicBall();

			//�����B
			return true;
		}

		void CMagicBallForward::Update(float deltaTime) {

			//�K��̐��ɒB������B
			if (m_createdNum == kMagicBallNum) {

				//���g��j���B
				DeleteGO(this);
			}

			//�^�C�}�[���X�V�B
			m_magicIntervalTimer -= deltaTime;

			if (m_magicIntervalTimer < 0.0f) {

				//���@�e�𐶐��B
				CreateMagicBall();

				//�^�C�}�[���������B
				m_magicIntervalTimer = kInterval;
			}
		}

		void CMagicBallForward::CreateMagicBall() {

			//���@�e�𐶐��B
			CMagicBallOne* magicBall = NewGO<CMagicBallOne>();

			//����ݒ�B
			magicBall->SetOwner(GetOwner());
			magicBall->SetMagicName(GetMagicName());
			magicBall->SetPosition(GetPosition());
			magicBall->SetMoveDirection(GetMoveDirection());
			magicBall->SetFeatureList(GetFeatureList());

			//���������̂Ő������Z�B
			m_createdNum++;
		}
	}
}