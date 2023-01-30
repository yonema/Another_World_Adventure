#include "YonemaEnginePreCompile.h"
#include "ShakeActor.h"
#include "GameActor.h"

namespace nsAWA {

	namespace {

		constexpr float kShakeMinAmount = -1.0f;	//�h�ꕝ�̍Œ�
		constexpr float kShakeValue = 6.0f;	//�h��̑傫��
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
		m_shakeTime -= deltaTime * 0.4f;

		if (m_shakeTime < FLT_EPSILON) {

			//�I�t�Z�b�g�����ɖ߂��B
			m_shakeActor->SetPositionOffset(CVector3::Zero());

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
		m_shakeVector.x = Random()->GetRangeFloat(shakeMin, shakeMax);
		m_shakeVector.y = Random()->GetRangeFloat(shakeMin, shakeMax);
		m_shakeVector.z = Random()->GetRangeFloat(shakeMin, shakeMax);

		//���W��ݒ�B
		m_shakeActor->SetPositionOffset(m_shakeVector);
	}
}