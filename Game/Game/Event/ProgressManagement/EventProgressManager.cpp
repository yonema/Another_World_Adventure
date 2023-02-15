#include "YonemaEnginePreCompile.h"
#include "EventProgressManager.h"
#include "EventProgress.h"


namespace nsAWA
{
	namespace nsEvent
	{
		CEventProgressManager* CEventProgressManager::m_instance = nullptr;

		void CEventProgressManager::ProgressEvent(std::string eventName)
		{
			for (auto event : m_latestEvents)
			{
				//���O����v���Ȃ��Ȃ�X�L�b�v
				if (event->GetName() != eventName)
				{
					continue;
				}

				//��v�����C�x���g��i�߂�
				event->Progress();

				//�C�x���g���܂��i�s���A�܂��͂��łɏI���ς݂Ȃ牽�����Ȃ�
				if (event->GetProgressState() != EnEventState::enCompleted)
				{
					return;
				}

				//�C�x���g���R���v���[�g���Ă���

				//�C�x���g���I���ς݂Ƃ��ă}�[�N
				event->MarkAsExpired();

				//�N���A�����C�x���g���X�g�ɃC�x���g����ǉ�
				m_cleardEventNameList.emplace_back(event->GetName());

				//�R���v���[�g�����C�x���g��O������Ƃ���C�x���g��ǉ�
				std::list<CEventProgress*> childEvents = event->GetChildren();

				for (CEventProgress* childEvent : childEvents)
				{
					//�N���A�����C�x���g��O������Ƃ���C�x���g�ɃN���A��������ʒm���Q�ƃJ�E���g��������
					childEvent->ClearPremise();

					//�ǉ�����\��̃C�x���g�����łɒǉ�����Ă��邩�`�F�b�N
					bool found = false;
					auto itr = m_latestEvents.begin();
					for (auto itr = m_latestEvents.begin();itr != m_latestEvents.end();itr++)
					{
						if ((*itr) == childEvent)
						{
							found = true;
							break;
						}
					}

					//�ǉ�����Ă��Ȃ��̂ŐV���ɒǉ�
					if (found == false)
					{
						m_latestEvents.emplace_back(childEvent);
					}
				}
				return;
			}

			//���s�s�\�ȃC�x���g�Ȃ̂ŉ������Ă��Ȃ��B
			return;
		}

		int CEventProgressManager::GetProgression(std::string eventName)
		{
			for (auto event : m_latestEvents)
			{
				if (eventName != event->GetName())
				{
					continue;
				}

				//���O�Ɉ�v����C�x���g������������A���̐i�s�x��Ԃ�
				return event->GetProgression();
			}

			return -1;
		}

		EnEventState CEventProgressManager::GetProgressState(std::string eventName)
		{
			for (auto event : m_latestEvents)
			{
				if (eventName != event->GetName())
				{
					continue;
				}

				//���O�Ɉ�v����C�x���g������������A���̐i�s�x��Ԃ�
				return event->GetProgressState();
			}

			return EnEventState::enNotReady;
		}

		void CEventProgressManager::SetClearedEvents(std::vector<std::string> clearedEventNameList)
		{
			for (auto clearedEventName : clearedEventNameList)
			{
				for (auto event : m_latestEvents)
				{
					//���O����v���Ȃ��Ȃ�X�L�b�v
					if (event->GetName() != clearedEventName)
					{
						continue;
					}

					//��v�����C�x���g���I���ς݂Ƃ��ă}�[�N
					event->MarkAsExpired();

					//�N���A�����C�x���g�Ȃ̂Ői�s�x�̓}�b�N�X�ɂ��Ă���
					event->SetProgression(event->GetMaxProgress());

					//�N���A�����C�x���g���X�g�ɃC�x���g����ǉ�
					m_cleardEventNameList.emplace_back(event->GetName());

					//�R���v���[�g�����C�x���g��O������Ƃ���C�x���g��ǉ�
					std::list<CEventProgress*> childEvents = event->GetChildren();

					for (CEventProgress* childEvent : childEvents)
					{
						//�N���A�����C�x���g��O������Ƃ���C�x���g�ɃN���A��������ʒm���Q�ƃJ�E���g��������
						childEvent->ClearPremise();

						//�ǉ�����\��̃C�x���g�����łɒǉ�����Ă��邩�`�F�b�N
						bool found = false;
						auto itr = m_latestEvents.begin();
						for (auto itr = m_latestEvents.begin(); itr != m_latestEvents.end(); itr++)
						{
							if ((*itr) == childEvent)
							{
								found = true;
								break;
							}
						}

						//�ǉ�����Ă��Ȃ��̂ŐV���ɒǉ�
						if (found == false)
						{
							m_latestEvents.emplace_back(childEvent);
						}
					}
					
					break;
				}
			}
		}


		std::vector<std::string> CEventProgressManager::GetProgressionList()
		{
			std::vector<std::string> progressionList;

			//�i�s���̃C�x���g�̐i�s�x�����i�[
			for (auto progressionEvent : m_latestEvents)
			{
				if (progressionEvent->GetProgressState() == EnEventState::enProgress)
				{
					char str[256];

					int progression = 0;
					
					//TODO:���݂̓C�x���g�̐i�s�x�������ł��Ă��Ȃ��悤�Ȃ̂ň�U���ׂĐi�s�x0�Ƃ���
					//int progression = progressionEvent->GetProgression();

					sprintf_s(str, sizeof(str), "%d", progression);

					std::string progressionString = str;

					progressionList.emplace_back(progressionString);
				}
			}

			return progressionList;
		}

		void CEventProgressManager::SetProgressionList(std::vector<std::string> progressionList)
		{
			int count = 0;

			for (auto latestEvent : m_latestEvents)
			{
				if (latestEvent->GetProgressState() != EnEventState::enProgress)
				{
					continue;
				}

				int progression = atoi(progressionList[count].c_str());

				latestEvent->SetProgression(progression);

				count++;
			}
		}
	}
}