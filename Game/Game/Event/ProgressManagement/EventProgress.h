#pragma once

namespace nsAWA
{
	namespace nsEvent
	{
		enum class EnEventState
		{
			enNotReady,	//�i�s�s��
			enProgress,	//�i�s��
			enCompleted,//����
			enExpired,	//�I���ς�
		};

		class CEventProgress
		{
		public:
			/**
			 * @brief �R���X�g���N�^
			 * @param name �C�x���g��
			 * @param maxProgress �ő�i�s�x
			*/
			CEventProgress(std::string name, int maxProgress)
			{
				m_eventName = name;
				m_maxProgress = maxProgress;
			}

			/**
			 * @brief ���̃C�x���g��O������Ƃ���C�x���g��ǉ�����
			 * @param event �ǉ�����C�x���g
			 * @return �ǉ������C�x���g�̃|�C���^(���\�b�h�`�F�C���Ƃ��Ďg�p�\)
			*/
			CEventProgress* AddFollowing(CEventProgress* event)
			{

				m_followingEvents.emplace_back(event);

				event->AddPremise();

				return event;
			}

			/**
			 * @brief �C�x���g�̐i�s�x��i�߂�
			*/
			void Progress()
			{
				if (m_progression >= m_maxProgress)
				{
					return;
				}

				m_progression++;

				if (m_progression == m_maxProgress)
				{
					m_eventState = EnEventState::enCompleted;
				}
			}

			/**
			 * @brief ���̃C�x���g�̑O������ƂȂ��Ă���C�x���g�̐������Z����
			*/
			void AddPremise()
			{
				m_referenceCount++;
			}

			/**
			 * @brief ���̃C�x���g�̑O������ƂȂ��Ă���C�x���g�̐������Z����(�O��C�x���g���N���A���ꂽ���ɌĂ΂��)
			*/
			void ClearPremise()
			{
				m_referenceCount--;
			}

			/**
			 * @brief ���̃C�x���g�͍����s�\��?
			 * @return �C�x���g�����s�\��(�I�����Ă��Ȃ��O������C�x���g���Ȃ���Ύ��s�\)
			*/
			bool IsExecutable()
			{
				return m_referenceCount == 0;
			}

			/**
			 * @brief ���̃C�x���g��O������Ƃ���C�x���g�̃��X�g���擾
			 * @return �C�x���g�̃��X�g
			*/
			const std::list<CEventProgress*>& GetChildren()
			{
				return m_followingEvents;
			}

			/**
			 * @brief �C�x���g�����ׂăN���A����?
			 * @return �C�x���g�̐i�s�x���ő�i�s�x�ƈꏏ�Ȃ�N���A
			*/
			bool IsClear()
			{
				return m_progression == m_maxProgress;
			}

			/**
			 * @brief �C�x���g�����擾
			 * @return �C�x���g��
			*/
			std::string GetName()
			{
				return m_eventName;
			}

			/**
			 * @brief �C�x���g�̐i�s�x���擾
			 * @return �C�x���g�̐i�s�x
			*/
			int GetProgression()
			{
				return m_progression;
			}

			/**
			 * @brief �C�x���g�̐i�s�x���Z�b�g����@�Z�[�u�f�[�^�̕������ȊO�͎g��Ȃ����Ƃ�z�肵�Ă���B
			 * @param progression �C�x���g�̐i�s�x
			*/
			void SetProgression(int progression)
			{
				m_progression = progression;
			}

			/**
			 * @brief �C�x���g�̐i�s��Ԃ��擾
			 * @return �C�x���g�̐i�s���
			*/
			EnEventState GetProgressState()
			{
				return m_eventState;
			}

			/**
			 * @brief �C�x���g���I���ς݂Ƃ��ă}�[�N
			*/
			void MarkAsExpired()
			{
				m_eventState = EnEventState::enExpired;
			}

			constexpr int GetMaxProgress() const noexcept
			{
				return m_maxProgress;
			}
		private:
			std::list<CEventProgress*> m_followingEvents;	//���̃C�x���g��O������Ƃ���C�x���g

			int m_referenceCount = 0;						//���̃C�x���g�̑O������ɂȂ�C�x���g�̐�

			int m_progression = 0;							//�i�s�x

			int m_maxProgress = 0;							//�ő�i�s�x

			std::string m_eventName = "";					//�C�x���g��

			EnEventState m_eventState = EnEventState::enProgress;	//�C�x���g�̐i�s���

		};
	}
}

