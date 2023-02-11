#include "Human.h"
#include "HumanTable.h"

namespace nsAWA
{
	namespace nsHumans
	{
		bool CHuman::Start()
		{

			return true;
		}

		void CHuman::Update(float deltaTime)
		{

			return;
		}

		void CHuman::OnDestroy()
		{
			Release();

			return;
		}

		void CHuman::Init(
			const char* name,
			const CVector3& position,
			const CQuaternion& rotation,
			const char* filePath
		)
		{
			m_name = name;

			Release();

			m_humanMR = NewGO<CHumanModelRenderer>(name);
			m_humanMR->Init(name, position, rotation, filePath);
			
			CheckEnableTalking();


			return;
		}

		void CHuman::Release()
		{
			//@attention ‚±‚ÌŠÖ”‚Í•¡”‰ñŒÄ‚Î‚ê‚Ä‚à–â‘è‚È‚¢‚æ‚¤‚É‚·‚é

			if (m_humanMR)
			{
				m_humanMR->Release();
				DeleteGO(m_humanMR);
				m_humanMR = nullptr;
			}

			return;
		}

		void CHuman::CheckEnableTalking()
		{
			auto itr = g_kNameToCsvFilePathParts.find(m_name);
			if (itr == g_kNameToCsvFilePathParts.end())
			{
				m_enableTalking = false;
				return;
			}

			m_enableTalking = true;

			return;
		}



	}
}
