#pragma once

namespace nsAWA {

	//共通のステータスクラス
	class CStatus : nsUtils::SNoncopyable
	{
	public:
		virtual int GetLevel()const = 0;
		virtual float GetHP()const = 0;
		virtual float GetMaxHP()const = 0;
		virtual float GetMP()const { return 0.0f; }
		virtual float GetMaxMP()const { return 0.0f; }
		virtual float GetSP()const { return 0.0f; }
		virtual float GetMaxSP()const { return 0.0f; }

		virtual float GetAttack(const std::string& attackType)const = 0;
		virtual float GetDeffence(const std::string& defenceType)const = 0;

		void AddWinceValue(float addValue) {

			//ひるみ値を加算。
			m_winceValue += addValue;
		}

		float GetWinceValue()const {

			//ひるみ値を取得。
			return m_winceValue;
		}

		float GetWinceDelimiter()const {

			//ひるみ値の区切りを取得。
			return m_winceDelimiter;
		}
	protected:
		float m_winceValue = 0.0f;		//ひるみ値
		float m_winceDelimiter = 0.0f;	//ひるみ値の区切り
	};
}

