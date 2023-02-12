#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayerAction;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}

	namespace nsPlayer {

		//プレイヤーの入力からアクションを起こすクラス
		class CPlayerInput : nsUtils::SNoncopyable
		{
		public:
			void Init(CPlayerAction* playerAction, nsPlayerAnimation::CPlayerAnimation* playerAnimation);

			void Release() {};

			void Update(bool isAnimationPlaying);

			void InputEnable() {

				//入力できる状態にする。
				m_canInput = true;
			}

			void InputDisable() {

				//入力できない状態にする。
				m_canInput = false;
			}

			void CoolTimeOn() {

				//クールタイムON。
				m_isCoolTime = true;
			}

			void CoolTimeOff() {

				//クールタイムOFF。
				m_isCoolTime = false;
			}

			void ChangeState();

		private:
			void InputSkillAction();

		private:
			CPlayerAction* m_playerAction = nullptr;	//プレイヤーアクションのポインタ
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;	//プレイヤーアニメーションのポインタ
			bool m_canInput = true;		//入力できる？
			bool m_isCoolTime = false;	//クールタイム中？
			float m_magicTime = 0.0f;		//魔法スキルの詠唱時間
		};
	}
}

