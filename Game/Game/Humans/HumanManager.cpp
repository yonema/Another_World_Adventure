#include "HumanManager.h"
#include "Human.h"
#include "../Player/Player.h"
#include "HumanTable.h"
#include "TalkToPlayer.h"

namespace nsAWA
{
	namespace nsHumans
	{
		const char* const CHumanManager::m_kRetargetSkeltonName = "PlayerSkelton";

		const char* const CHumanManager::m_kHumanPrefix = "Humans_";



		bool CHumanManager::Start()
		{
			m_talkToPlayer = NewGO<CTalkToPlayer>("TalkToPlayer");
			m_talkToPlayer->Init(this);

			return true;
		}

		void CHumanManager::Update(float deltaTime)
		{
			CheckBaseHumanLoading();

			if (m_playerRef == nullptr)
			{
				SetPlayerRef(FindGO<nsPlayer::CPlayer>("Player"));
			}

			return;
		}

		void CHumanManager::OnDestroy()
		{
			Release();

			return;
		}



		void CHumanManager::Release()
		{
			if (m_humanMap.empty() != true)
			{
				for (auto& human : m_humanMap)
				{
					if (human.second == nullptr)
					{
						continue;
					}

					human.second->Release();
					DeleteGO(human.second);
					human.second = nullptr;
				}
			}

			m_humanMap.clear();

			if (m_baseHumanMR)
			{
				DeleteGO(m_baseHumanMR);
				m_baseHumanMR = nullptr;
			}

			if (m_talkToPlayer)
			{
				DeleteGO(m_talkToPlayer);
				m_talkToPlayer = nullptr;
			}

			return;
		}

		void CHumanManager::GenerateBase(bool loadingAsynchronous)
		{
			if (m_baseLoadingState != EnLoadingState::enBeforeLoading)
			{
				return;
			}


			SModelInitData modelInitData;
			modelInitData.modelFilePath = g_kNameToModelFilePath.at(g_kBaseHumanName);
			modelInitData.animInitData.Init(
				static_cast<int>(EnHumanAnimType::enNum), g_kAnimFilePaths);
			modelInitData.retargetSkeltonName = m_kRetargetSkeltonName;

			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterAnimationBank);
			if (loadingAsynchronous)
			{
				modelInitData.SetFlags(EnModelInitDataFlags::enLoadingAsynchronous);
			}

			m_baseHumanMR = NewGO<CModelRenderer>();
			// �\�����Ȃ��悤�ɂ���
			m_baseHumanMR->SetScale(0.0f);
			m_baseHumanMR->Init(modelInitData);

			if (loadingAsynchronous)
			{
				m_baseLoadingState = EnLoadingState::enNowLoading;
			}
			else
			{
				DeleteGO(m_baseHumanMR);
				m_baseHumanMR = nullptr;
				m_baseLoadingState = EnLoadingState::enAfterLoading;
			}

			return;
		}


		void CHumanManager::GenerateHuman(
			const std::string& objName, const CVector3& position, const CQuaternion& rotation)
		{
			// base���f���̃��[�h�`�F�b�N

			if (m_baseLoadingState != EnLoadingState::enAfterLoading)
			{
				switch (m_baseLoadingState)
				{
				case EnLoadingState::enBeforeLoading:
					// Base�𐶐����Ă���AHuman�̐������J�n����B
					GenerateBase();
					break;

				case EnLoadingState::enNowLoading:
					// Human�𐶐��ł��Ȃ�
					nsGameWindow::MessageBoxError(
						L"Human�̃x�[�X���f�������[�h���̂��߁AHuman�𐶐��ł��܂���B");
					return;
					break;

				default:
					// Human�𐶐��ł��Ȃ�
					nsGameWindow::MessageBoxError(
						L"�s���̎��ԁBHuman�𐶐��ł��܂���B");
					return;
					break;
				}

			}


			// ���O��Human������

			const auto* name = objName.c_str();
			static const size_t kPrefixLen = strlen(m_kHumanPrefix);
			name += kPrefixLen;

			auto itr = g_kNameToModelFilePath.find(name);

			if (itr == g_kNameToModelFilePath.end())
			{
				auto wStr = nsUtils::GetWideStringFromString(name);
				wStr += L" ��HumanManager�ɓo�^����Ă��܂���B";
				nsGameWindow::MessageBoxWarning(wStr.c_str());
				return;
			}

			// Human�𐶐�

			static CQuaternion rot;
			rot.SetRotationXDeg(-90.0f);
			auto* human = NewGO<CHuman>(name);
			human->Init(name, position, rotation * rot, itr->second);

			if (m_humanMap.find(name) != m_humanMap.end())
			{
				auto wstr = nsUtils::GetWideStringFromString(name);
				wstr.erase(wstr.end() - 1);
				wstr += L"��������������Ă��܂��B";
				nsGameWindow::MessageBoxWarning(wstr.c_str());
			}
			m_humanMap.emplace(name, human);


			return;
		}


		void CHumanManager::DeleteHuman(const std::string& name)
		{
			auto itr = m_humanMap.find(name);

			if (itr == m_humanMap.end()) 
			{
				return;
			}

			DeleteGO(itr->second);

			m_humanMap.erase(itr);

			return;
		}




		void CHumanManager::CheckBaseHumanLoading() noexcept
		{
			if (m_baseLoadingState != EnLoadingState::enNowLoading || m_baseHumanMR == nullptr)
			{
				return;
			}

			if (m_baseHumanMR->IsLoadingAsynchronous() != true)
			{
				m_baseLoadingState = EnLoadingState::enAfterLoading;
				DeleteGO(m_baseHumanMR);
				m_baseHumanMR = nullptr;
			}

			return;
		}


		void CHumanManager::ActivateAllHumans()
		{
			if (m_isPlayerInTown)
			{
				return;
			}


			for (auto& human : m_humanMap)
			{
				human.second->HumanActivate();
			}

			m_isPlayerInTown = true;

			return;
		}

		void CHumanManager::DeactivateAllHumans()
		{
			if (m_isPlayerInTown != true)
			{
				return;
			}

			for (auto& human : m_humanMap)
			{
				human.second->HumanDeactivate();
			}

			m_isPlayerInTown = false;

			return;
		}

	}
}
