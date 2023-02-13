#include "WorldParts.h"
#include "../../YonemaEngine/Geometries/AABB.h"
#include "../Facility/FacilityType.h"

namespace nsAWA
{
	namespace nsWorld
	{
		const char* const CWorldParts::m_kPartsPrefixArray[static_cast<int>(EnPartsType::enNum)] =
		{
			"Town_",
			"Building_",
			"Meadow_",
			"Mountain_",
			"Forest_",
			"Facility_"
		};
		const char* const CWorldParts::m_kFacilityPrefix = "Assets/Models/Town/Facility_";


		CWorldParts::~CWorldParts()
		{
			Terminate();

			return;
		}

		void CWorldParts::Terminate()
		{
			for (auto& modelRenderer : m_modelRendererArray)
			{
				DeleteGO(modelRenderer);
				modelRenderer = nullptr;
			}
			m_modelRendererArray.clear();


			for (auto& facility : m_facilityList)
			{
				DeleteGO(facility);
				facility = nullptr;
			}
			m_facilityList.clear();

			return;
		}

		bool CWorldParts::PushWorldData(
			const std::string& objName,
			const CVector3& pos,
			const CQuaternion& rot,
			const CVector3& scale
		)
		{
			bool match = false;
			int idx = 0;
			for (idx = 0; idx < static_cast<int>(EnPartsType::enNum); idx++)
			{
				match = nsUtils::ForwardMatchName(objName.c_str(), m_kPartsPrefixArray[idx]);

				if (match)
				{
					break;
				}
			}

			if (match != true)
			{
				return false;
			}

			bool isFacility = false;
			std::string filePath = {};
			switch (static_cast<EnPartsType>(idx))
			{
			case EnPartsType::enTown:
			case EnPartsType::enBuilding:
				filePath = "Assets/Models/Town/";
				break;
			case EnPartsType::enMeadow:
				filePath = "Assets/Models/Meadow/";
				break;
			case EnPartsType::enMountain:
				filePath = "Assets/Models/Mountain/";
				break;
			case EnPartsType::enForest:
				filePath = "Assets/Models/Forest/";
				return false;
			case EnPartsType::enFacility:
				filePath = "Assets/Models/Town/";
				isFacility = true;
				break;
			}

			filePath += objName.c_str();
			filePath += ".fbx";

			bool res = true;
			if (isFacility)
			{
				m_facilityTRSMap.emplace(filePath, STRS(pos, rot, scale));
			}
			else
			{
				m_modelTRSListMap[filePath].emplace_back(pos, rot, scale);
			}

			return res;
		}

		void CWorldParts::Build(nsHumans::CHumanManager* humanManager)
		{
			BuildModel();

			BuildFacility(humanManager);

			return;
		}


		void CWorldParts::BuildModel()
		{
			m_modelRendererArray.reserve(m_modelTRSListMap.size());

			for (const auto& TRSList : m_modelTRSListMap)
			{
				SModelInitData modelInitData;
				modelInitData.modelFilePath = TRSList.first;
				modelInitData.SetFlags(EnModelInitDataFlags::enShadowCaster);
				modelInitData.SetFlags(EnModelInitDataFlags::enRegisterTextureBank);
				modelInitData.maxInstance = static_cast<unsigned int>(TRSList.second.size());

				auto* mr = NewGO<CModelRenderer>();

				if (modelInitData.maxInstance <= 1)
				{
					// 通常描画
					const auto& itr = TRSList.second.begin();
					mr->SetPosition(itr->pos);
					mr->SetRotation(itr->rot);
					mr->SetScale(itr->scale);
					mr->Init(modelInitData);
				}
				else
				{
					// インスタンシング描画
					mr->Init(modelInitData);
					auto* mWorldArray = mr->GetWorldMatrixArrayRef();

					int idx = 0;
					for (const auto& trs : TRSList.second)
					{
						(*mWorldArray)[idx++] = trs.CalcMatrix();
					}

				}

				m_modelRendererArray.emplace_back(mr);
			}


			return;
		}

		void CWorldParts::BuildFacility(nsHumans::CHumanManager* humanManager)
		{
			for (const auto& facilityTRS : m_facilityTRSMap)
			{
				const char* sarchName = facilityTRS.first.c_str();

				sarchName += strlen(m_kFacilityPrefix);

				bool match = false;
				int idx = 0;
				for (idx = 0; idx < static_cast<int>(EnFacilityType::enNum); idx++)
				{
					match = nsUtils::ForwardMatchName(sarchName, g_kFacilityNameArray[idx]);

					if (match)
					{
						break;
					}
				}

				if (match != true)
				{
					UnexpectedLevelObject(facilityTRS.first);
					continue;
				}


				nsFacility::IFacilityBase* facility = nullptr;
				nsFacility::CTown* town = nullptr;

				switch (static_cast<EnFacilityType>(idx))
				{
				case EnFacilityType::enTown:
					town = NewGO<nsFacility::CTown>(sarchName);
					town->SetHumanManagerRef(humanManager);
					facility = town;
					break;
				case EnFacilityType::enInn:
					facility = NewGO<nsFacility::CInn>(sarchName);
					break;
				case EnFacilityType::enShop:
					facility = NewGO<nsFacility::CShop>(sarchName);
					break;
				case EnFacilityType::enForge:
					facility = NewGO<nsFacility::CForge>(sarchName);
					break;
				case EnFacilityType::enGuild:
					facility = NewGO<nsFacility::CGuild>(sarchName);
					break;
				}

				const char* filePath = g_kFacilityCollisionFilePath_Town;

				if (static_cast<EnFacilityType>(idx) != EnFacilityType::enTown)
				{
					filePath = g_kFacilityCollisionFilePath_Mini;
				}

				facility->Init(
					facilityTRS.second.pos, 
					facilityTRS.second.rot, 
					facilityTRS.second.scale, 
					filePath
				);

				m_facilityList.emplace_back(facility);
			}

			return;
		}

		void CWorldParts::UnexpectedLevelObject(const std::string& objName) const noexcept
		{
			std::wstring wstr = L"予想外のオブジェクト ";
			wstr += nsUtils::GetWideStringFromString(objName);
			wstr.erase(wstr.end() - 1);
			wstr += L" がレベルで読み込まれています。";
			nsGameWindow::MessageBoxWarning(wstr.c_str());

			return;
		}



	}
}