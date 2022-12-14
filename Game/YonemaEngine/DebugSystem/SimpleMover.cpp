#include "SimpleMover.h"
#include "../Input/InputManager.h"

namespace nsYMEngine
{
	namespace nsDebugSystem
	{
		bool CSimpleMover::Start()
		{
			return true;
		}
		void CSimpleMover::OnDestroy()
		{
			return;
		}
		void CSimpleMover::Update(float deltaTime)
		{
			CalcForward();
			CalcRight();

			Turn(deltaTime);
			Move(deltaTime);

			return;
		}

		void CSimpleMover::CalcForward() noexcept 
		{
			m_forward = nsMath::CVector3::Front();
			m_rotation.Apply(m_forward);
			m_forward.Normalize();
			return;
		}

		void CSimpleMover::CalcRight() noexcept
		{
			m_right.Cross(nsMath::CVector3::Up(), GetForward());
			m_right.Normalize();
			return;
		}

		void CSimpleMover::Turn(float deltaTime) noexcept
		{
			// 入力値取得
			auto* keyboard = CYonemaEngine::GetInstance()->GetInput()->GetKeyboard();
			float inputTurnRight = 
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enLeft) ? -1.0f : 0.0f;
			inputTurnRight += 
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enRight) ? 1.0f : 0.0f;
			float inputTurnUp = 
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enUp) ? 1.0f : 0.0f;
			inputTurnUp +=
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enDown) ? -1.0f : 0.0f;

			float turnSpeed = m_turnSpeed * deltaTime;

			const auto forward = GetForward();
			
			// Y軸(横方向)回転

			// 現在の横方向の角度を計算
			float horizontalAngle = nsMath::RadToDeg(atan2(forward.x, forward.z));
			nsMath::CQuaternion horizontalRot;
			horizontalAngle += inputTurnRight * turnSpeed;
			horizontalRot.SetRotationYDeg(horizontalAngle);


			// ローカルX軸(縦方向)回転

			auto forwardXZ = GetForward();
			forwardXZ.y = 0.0f;
			float forwardXZLen = forwardXZ.Length();
			// 現在の縦方向の角度を計算
			float verticalAngle = nsMath::RadToDeg(atan2(-forward.y, forwardXZLen));
			verticalAngle += inputTurnUp * turnSpeed;
			// 角度制限
			verticalAngle = std::min(verticalAngle, 45.0f);
			verticalAngle = std::max(verticalAngle, -45.0f);

			auto axisRight = GetRight();
			axisRight.y = 0.0f;
			axisRight.Normalize();
			nsMath::CQuaternion verticalRot;
			verticalRot.SetRotationDeg(axisRight, verticalAngle);

			m_rotation.Multiply(horizontalRot, verticalRot);

			return;
		}

		void CSimpleMover::Move(float deltaTime) noexcept
		{
			// 入力値取得
			auto* keyboard = CYonemaEngine::GetInstance()->GetInput()->GetKeyboard();
			float inputMoveForward =
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enW) ? 1.0f : 0.0f;
			inputMoveForward +=
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enS) ? -1.0f : 0.0f;
			float inputMoveRight =
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enA) ? -1.0f : 0.0f;
			inputMoveRight +=
				keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enD) ? 1.0f : 0.0f;

			bool isMoveUp = keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enQ);
			bool isMoveDown = keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enE);

			bool isDush = keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enLShift);
			bool isFastDush = keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enRShift);
			bool isWalk = keyboard->IsPress(nsInput::CKeyboard::EnKeyButton::enCtrl);


			// 移動
			auto moveVec = nsMath::CVector3::Zero();
			float moveSpeed = m_moveSpeed * deltaTime;
			if (isDush)
			{
				moveSpeed *= 2.0f;
			}
			else if (isFastDush)
			{
				moveSpeed *= 10.0f;
			}
			if (isWalk)
			{
				moveSpeed *= 0.5f;
			}

			// XZ平面での移動する方向を計算
			auto moveForward = GetForward();
			auto moveRight = GetRight();
			moveForward.y = 0.0f;
			moveRight.y = 0.0f;

			// XZ平面での移動
			moveVec += moveForward * inputMoveForward * moveSpeed;
			moveVec += moveRight * inputMoveRight * moveSpeed;

			// Y軸縦移動
			if (isMoveUp)
			{
				moveVec.y += moveSpeed;
			}
			if (isMoveDown)
			{
				moveVec.y -= moveSpeed;
			}

			m_position += moveVec;

			return;
		}



		void CSimpleMover::MoveCameraBySimpleMover() noexcept
		{
			// MoveCameraBySimpleMover
			MainCamera()->SetPosition(GetPosition());
			nsMath::CVector3 toTarget = GetForward();
			toTarget.Scale(5.0f);
			MainCamera()->SetTargetPosition(GetPosition() + toTarget);

			return;
		}

	}
}