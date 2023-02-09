#include "YonemaEnginePreCompile.h"
#include "EventProgressManager.h"
#include "EventProgress.h"


namespace nsAWA
{
	namespace nsEvent
	{
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

				//�C�x���g�����S�ɏI����Ă��Ȃ��Ȃ�I��
				if (event->IsClear() == false)
				{
					return;
				}

				//�C�x���g���R���v���[�g���Ă���

				//�R���v���[�g�����C�x���g��O������Ƃ���C�x���g��ǉ�
				std::list<CEventProgress*> childEvents = event->GetChildren();

				for (CEventProgress* childEvent : childEvents)
				{
					//�N���A�����C�x���g��O������Ƃ���C�x���g�ɃN���A��������ʒm���Q�ƃJ�E���g��������
					childEvent->ClearPremise();

					//�ǉ�����\��̃C�x���g�����łɒǉ�����Ă��邩�`�F�b�N()
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

					if (found == false)
					{
						m_latestEvents.emplace_back(childEvent);
					}
				}

				m_latestEvents.remove(event);
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

				return event->GetProgression();
			}

			return -1;
		}
	}
}