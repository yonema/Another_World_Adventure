#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kCanPlayerMoveInput = 0.01f;	//�ړ����͂����肳���Œ�l
		}

		void CPlayerInput::Init(CPlayerAction* playerAction) {

			//���͂ɂ���čs�������邽�߁A�v���C���[�A�N�V�����N���X�̃|�C���^���󂯎��B
			m_playerAction = playerAction;
		}

		void CPlayerInput::Update() {

			//�ړ����́B
			{
				//�ړ����͂��󂯎��B
				auto inputX = Input()->GetVirtualAxis(EnAxisMapping::enRight);
				auto inputZ = Input()->GetVirtualAxis(EnAxisMapping::enForward);
				
				//���͂�����Ă��邩�B
				if (std::fabsf(inputX) > kCanPlayerMoveInput
					|| std::fabsf(inputZ) > kCanPlayerMoveInput
				)
				{
					//�ړ��B
					m_playerAction->Move(
						inputX,
						inputZ
					);
				}
			}
		}
	}
}