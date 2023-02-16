#pragma once

namespace nsAWA
{
	namespace nsEvent
	{
		class CEventProgressManager;

		class CEventSaveData
		{
		public:
			void Save();

			void Load();

		private:

			void SaveClearedEventData(CEventProgressManager* eventManager);

			void SaveEventProgressionData(CEventProgressManager* eventManager);

		private:
			const wchar_t* kEventDataCSVFilePath = L"Assets/CSV/EventData.csv";	//�C�x���g�f�[�^��CSV�t�@�C���p�X
		private:
			std::list<std::vector<std::string>> m_eventSaveData;		//�i�s���̃C�x���g�����L�^�����f�[�^

		};
	}
}

