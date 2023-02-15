#pragma once
#include "EventProgress.h"

namespace nsAWA
{
	namespace nsEvent
	{
		class CEventProgressManager : nsUtils::SNoncopyable
		{
		private:
			CEventProgressManager(){}
			~CEventProgressManager(){}

		public:
			/**
			 * @brief �C���X�^���X���쐬
			 * @return �C���X�^���X
			*/
			static inline CEventProgressManager* CreateInstance() noexcept
			{
				if (m_instance == nullptr)
				{
					m_instance = new CEventProgressManager();
				}
				return m_instance;
			}

			/**
			 * @brief �C���X�^���X���擾
			 * @return �C���X�^���X
			*/
			static inline CEventProgressManager* GetInstance() noexcept
			{
				return m_instance;
			}

			/**
			 * @brief �C���X�^���X���폜
			 * @return 
			*/
			static void DeleteInstance() noexcept
			{
				if (m_instance == nullptr)
				{
					return;
				}
				delete m_instance;
				m_instance = nullptr;
			}

			/**
			 * @brief ���[�g�C�x���g��ǉ�
			 * @param event ���[�g�ɒǉ�����C�x���g
			 * @return �ǉ������C�x���g�̃|�C���^(���\�b�h�`�F�C���Ƃ��Ďg�p�\)
			*/
			CEventProgress* AddRootEvent(CEventProgress* event)
			{
				m_latestEvents.emplace_back(event);

				return event;
			}

			/**
			 * @brief ���O�Ŏw�肵���C�x���g�̐i�s�x��i�߂�
			 * @param eventName �i�߂�C�x���g��
			*/
			void ProgressEvent(std::string eventName);

			/**
			 * @brief ���O�Ŏw�肵���C�x���g�̐i�s�x���擾����
			 * @param eventName �擾����C�x���g��
			 * @return �C�x���g�̐i�s�x(�i�s�ł��Ȃ���ԂȂ�-1)
			*/
			int GetProgression(std::string eventName);

			/**
			 * @brief ���O�Ŏw�肵���C�x���g�̐i�s��Ԃ��擾����
			 * @param eventName �擾����C�x���g��
			 * @return �C�x���g�̐i�s���
			*/
			EnEventState GetProgressState(std::string eventName);


			constexpr const auto& GetLatestEvents() const noexcept
			{
				return m_latestEvents;
			}

			std::vector<std::string> GetProgressionList();
		private:
			static CEventProgressManager* m_instance;		//�C���X�^���X
			
			std::list<CEventProgress*> m_latestEvents;		//�i�s�x���`�F�b�N����C�x���g(�O������ɂ���Ď��s�ł��Ȃ������܂�)
		
			std::vector<std::string> m_cleardEventNameList;	//�N���A�����C�x���g�̃��X�g(�N���A�������Ɋi�[)

			std::vector<std::string> m_progressionList;		//�N���A���Ă��Ȃ��C�x���g�̂����i�s���̂��̂̐i�s�x�̃��X�g
		};
	}
}
