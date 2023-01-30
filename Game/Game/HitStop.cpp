#include "YonemaEnginePreCompile.h"
#include "HitStop.h"
#include "GameActor.h"

namespace nsAWA {

	void CHitStop::Init(IGameActor* target, float hitStopTime) {

		//�^�[�Q�b�g��ݒ�B
		m_target = target;

		//�^�[�Q�b�g�̃A�j���[�V�������x��ۊǁB
		m_targetAnimationSpeed = m_target->GetModelRenderer()->GetAnimationSpeed();

		//�q�b�g�X�g�b�v���Ԃ�ݒ�B
		m_timer = hitStopTime;

		//�^�[�Q�b�g���q�b�g�X�g�b�v��Ԃɐݒ�B
		m_target->SetHitStop(true);

		//�^�[�Q�b�g�̃A�j���[�V�������x��0�ɐݒ�B
		m_target->GetModelRenderer()->SetAnimationSpeed(0.0f);
	}

	void CHitStop::Update(float deltaTime) {

		//�^�C�}�[���X�V�B
		m_timer -= deltaTime;

		//�^�C�}�[��0�ɂȂ�����B
		if (m_timer < 0.0f) {

			//�^�[�Q�b�g�̃q�b�g�X�g�b�v��Ԃ������B
			m_target->SetHitStop(false);

			//�^�[�Q�b�g�̃A�j���[�V�������x��ʏ�ɖ߂��B
			m_target->GetModelRenderer()->SetAnimationSpeed(m_targetAnimationSpeed);

			//���g��j���B
			DeleteGO(this);
		}
	}
}