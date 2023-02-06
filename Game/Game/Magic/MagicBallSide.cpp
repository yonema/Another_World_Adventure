#include "YonemaEnginePreCompile.h"
#include "MagicBallSide.h"
#include "MagicBallOne.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr short kMagicBallNum = 3;	//���@�̐�
			constexpr float kInterval = 15.0f;	//���@�e�̊Ԋu
		}

		bool CMagicBallSide::Start() {

			//���@�̊Ԋu�̒��������߂�B
			float magicIntervalLength = kInterval * (kMagicBallNum - 1);

			//�S�̂̒����̔����̒��������߂�B
			float magicIntervalLengthHalf = magicIntervalLength / 2.0f;

			//�����������߂�B
			CVector3 sideDirection = Cross(GetMoveDirection(), CVector3::AxisY());
			sideDirection.Normalize();

			//���@�̊J�n�ʒu��ݒ�B
			CVector3 startMagicPosition = GetPosition() - sideDirection * magicIntervalLengthHalf;

			//�K�v�Ȑ��������@�e�𐶐��B
			for (int magicNum = 0; magicNum < kMagicBallNum; magicNum++) {

				//���@�e�𐶐��B
				CMagicBallOne* magicBall = NewGO<CMagicBallOne>();

				//����ݒ�B
				magicBall->SetOwner(GetOwner());
				magicBall->SetMagicName(GetMagicName());
				magicBall->SetPosition(startMagicPosition);
				magicBall->SetMoveDirection(GetMoveDirection());
				magicBall->SetFeatureList(GetFeatureList());

				//���̍��W�𒲐��B
				startMagicPosition += sideDirection * kInterval;
			}

			//�������I������̂Ŏ��g��j���B
			DeleteGO(this);

			//�����B
			return true;
		}
	}
}