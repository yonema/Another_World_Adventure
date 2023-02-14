#include "YonemaEnginePreCompile.h"
#include "CameraAction.h"
#include "../Player/Player.h"

namespace nsAWA {

	namespace nsCamera {

		namespace {

			const CVector3 kStartAddCameraVec = { 0.0f,10.0f,-30.0f };		//�J�n���_�ł̉��Z�x�N�g��
			constexpr const float kRotationSpeed = 2.0f;					//��]���x
			constexpr const float kAddPlayerPosition = 10.0f;				//�v���C���[�̋�����������邽�߂̉��Z�X�J���[
			constexpr float kDirectionUpMax = -0.5f;						//�J�������ǂꂭ�炢��������邩
			constexpr float kDirectionDownMax = 0.8f;						//�J�������ǂꂭ�炢���������邩
		}

		void CCameraAction::Init(nsPlayer::CPlayer* player) {

			//�v���C���[�̃|�C���^���擾�B
			m_player = player;

			//���Z�x�N�g�����������B
			m_addCameraVec = kStartAddCameraVec;
		}

		void CCameraAction::Update() {

			//�v���C���[�̍��W���擾�B
			CVector3 playerPosition = m_player->GetPosition();

			//�v���C���[�̗h��Ƃ͔��΂ɃI�t�Z�b�g��ݒ�B
			CVector3 cameraPositionOffset = m_player->GetPositionOffset();
			cameraPositionOffset *= -1.0f;

			//�����_�𒲐��B
			playerPosition.y += kAddPlayerPosition;

			//�����_��ݒ�B
			m_targetPosition = playerPosition + cameraPositionOffset;

			//���_��ݒ�B
			m_position = m_targetPosition + m_addCameraVec;
		}

		void CCameraAction::Rotate(float rotateUp, float rotateRight) {

			//���݂̂̉��Z�x�N�g�������ꎞ�ۑ��B
			CVector3 toCameraPosOld = m_addCameraVec;

			//Y������̉�]�B
			CQuaternion qRotY;
			qRotY.SetRotationDeg(CVector3::AxisY(), kRotationSpeed * rotateRight);
			qRotY.Apply(m_addCameraVec);

			//X������̉�]�B
			CVector3 axisX;
			axisX.Cross(CVector3::AxisY(), m_addCameraVec);
			axisX.Normalize();
			qRotY.SetRotationDeg(axisX, kRotationSpeed * rotateUp);
			qRotY.Apply(m_addCameraVec);

			//���Z�x�N�g���̕��������߂�B
			CVector3 toPosDir = m_addCameraVec;
			toPosDir.Normalize();

			//�J�����p�x���C���B
			//�p�x����𒴂��Ă���Ȃ��]�����Ȃ��B
			if (toPosDir.y < kDirectionUpMax) {
				//������B
				m_addCameraVec = toCameraPosOld;
			}
			else if (toPosDir.y > kDirectionDownMax) {
				//�������B
				m_addCameraVec = toCameraPosOld;
			}

		}

	}
}