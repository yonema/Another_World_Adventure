#pragma once
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsDebugRenderers
		{
			class CPhysicsDebugLineGenericRenderer : public nsRenderers::IGenericRenderer
			{
			private:
				enum class EnDescRangeType : unsigned int
				{
					enCbvForSceneData,
					enNumDescRangeTypes
				};
				enum class EnRootParameterType : unsigned int
				{
					enSceneData,
					enNumRootParamerterTypes
				};

				static const wchar_t* const m_kVsFilePath;
				static const char* const m_kVsEntryFuncName;
				static const wchar_t* const m_kPsFilePath;
				static const char* const m_kPsEntryFuncName;

			private:
				void CreateRootParameter(
					std::vector<CD3DX12_DESCRIPTOR_RANGE1>* pDescTblRanges,
					std::vector<CD3DX12_ROOT_PARAMETER1>* pRootParameters
				) const noexcept override;

				inline std::wstring CreateRootSignatureName() const noexcept override
				{
					return L"PhysicsDebugLineGenericRenderer";
				}

				bool CreateShader(
					nsDx12Wrappers::CBlob* pVsBlob,
					nsDx12Wrappers::CBlob* pPsBlob
				) const noexcept override;

				void CreateInputLayout(
					std::vector<D3D12_INPUT_ELEMENT_DESC>* pInputLayout) const noexcept override;

				inline D3D12_PRIMITIVE_TOPOLOGY_TYPE SetUpPrimitiveTopologyType() const noexcept override
				{
					// ƒ‰ƒCƒ“‚ðˆø‚­
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
				}

				inline std::wstring CreatePipelineStateName() const noexcept override
				{
					return L"PhysicsDebugLineGenericRenderer";
				}

			public:
				constexpr CPhysicsDebugLineGenericRenderer() = default;
				~CPhysicsDebugLineGenericRenderer() = default;

			private:

			};

		}
	}
}