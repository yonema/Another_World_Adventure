#include "YonemaEnginePreCompile.h"
#include "EventSaveData.h"
#include "EventProgressManager.h"
#include "../../CSV/CSVManager.h"


namespace nsAWA
{
	namespace nsEvent
	{
		void CEventSaveData::Save()
		{
			//�f�[�^����j���B
			m_eventSaveData.clear();

			CEventProgressManager* eventManager = nsEvent::CEventProgressManager::CreateInstance();

			//�C�x���g�̃N���A�󋵂��Z�[�u
			SaveClearedEventData(eventManager);

			//�i�s���̃C�x���g�̐i�s�x���Z�[�u
			SaveEventProgressionData(eventManager);

			//�f�[�^��ۑ��B
			nsCSV::CCsvManager csvManager;
			csvManager.SaveCSV(kEventDataCSVFilePath, m_eventSaveData);
		}

		void CEventSaveData::Load()
		{
			//���݊i�[����Ă���f�[�^������Δj��
			m_eventSaveData.clear();

			//�C�x���g�f�[�^�i�[�p��CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kEventDataCSVFilePath);

			//�f�[�^�̃C�e���[�^���擾�B
			auto data = csvManager.GetCsvData();
			auto itr = data.begin();

			nsEvent::CEventProgressManager* eventManager = nsEvent::CEventProgressManager::CreateInstance();
			//�N���A�����N�G�X�g�����[�h
			eventManager->SetClearedEvents(*itr);
			itr++;

			//�i�s���̃N�G�X�g�̐i�s�x�����[�h
			eventManager->SetProgressionList(*itr);
		}

		void CEventSaveData::SaveClearedEventData(CEventProgressManager* eventManager)
		{
			m_eventSaveData.emplace_back(eventManager->GetClearedEvents());
		}

		void CEventSaveData::SaveEventProgressionData(CEventProgressManager* eventManager)
		{
			m_eventSaveData.emplace_back(eventManager->GetProgressionList());
		}
	}
}