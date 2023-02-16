#pragma once
#include "Attribute.h"

namespace nsAWA {

	//���ʂ̃X�e�[�^�X�N���X
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

			//�Ђ�ݒl�����Z�B
			m_winceValue += addValue;
		}

		void SubWinceValue(float subValue) {

			//�Ђ�ݒl�����Z�B
			m_winceValue -= subValue;
		}

		float GetWinceValue()const {

			//�Ђ�ݒl���擾�B
			return m_winceValue;
		}

		float GetWinceDelimiter()const {

			//�Ђ�ݒl�̋�؂���擾�B
			return m_winceDelimiter;
		}

		const EnAttribute& GetAttribute()const {

			//�������擾�B
			return m_attribute;
		}

		void SetAttribute(const EnAttribute& attribute) {

			//������ݒ�B
			m_attribute = attribute;
		}

	protected:
		float m_winceValue = 0.0f;		//�Ђ�ݒl
		float m_winceDelimiter = 0.0f;	//�Ђ�ݒl�̋�؂�
		EnAttribute m_attribute = EnAttribute::enNone;//����
	};
}

