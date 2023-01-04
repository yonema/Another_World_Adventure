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

			void Update(bool isAnimationPlaying);

			void CoolTimeOn() {

				//クールタイム中にする。
				m_isCoolTime = true;
			}

			void CoolTimeOff() {

				//クールタイムを外す。
				m_isCoolTime = false;
			}

			bool GetCoolTime()const {

				return m_isCoolTime;
			}

			void ChangeState();

		private:
			void InputSkillAction();

		private:
			CPlayerAction* m_playerAction = nullptr;	//プレイヤーアクションのポインタ
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;	//プレイヤーアニメーションのポインタ
			bool m_isCoolTime = false;		//クールタイム中？
		};
	}
}

