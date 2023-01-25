#include "YonemaEnginePreCompile.h"
#include "ShakeActor.h"
#include "GameActor.h"

namespace nsAWA {

	namespace {

		constexpr float kShakeMinAmount = 0.8f;	//�h�ꕝ�̍Œ�
		constexpr float kShakeValue = 8.0f;	//�h��̑傫��
	}

	void CShakeActor::Init(IGameActor* shakeActor, float shakeTime) {

		//�������B
		m_shakeActor = shakeActor;
		m_shakeTime = shakeTime;

		//�A�N�^�[�̌����W���擾�B
		m_actorOldPosition = m_shakeActor->GetPosition();
	}

	void CShakeActor::Update(float deltaTime) {

		//�h�ꎞ�Ԃ��X�V�B
		m_shakeTime -= deltaTime;

		if (m_shakeTime < FLT_EPSILON) {

			//���W�����ɖ߂��B
			m_shakeActor->SetPosition(m_actorOldPosition);

			//���̋@�\��j���B
			DeleteGO(this);

			//�I���B
			return;
		}

		//�h�ꕝ�����߂�B
		float shakeAmount = m_shakeTime * kShakeValue;

		//�h�ꕝ�̍Œ�l�ƍő�l�����߂�B
		float shakeMax = shakeAmount;
		float shakeMin = shakeMax * kShakeMinAmount;

		//�h�ꕝ��ݒ�B
		CVector3 shakeVector = CVector3::Zero();
		nsUtils::CRandom random;
		shakeVector.x = random.GetRangeFloat(shakeMin, shakeMax);
		shakeVector.y = random.GetRangeFloat(shakeMin, shakeMax);
		shakeVector.z = random.GetRangeFloat(shakeMin, shakeMax);

		//���W��ݒ�B
		m_shakeActor->SetPosition(m_actorOldPosition + shakeVector);
	}
}