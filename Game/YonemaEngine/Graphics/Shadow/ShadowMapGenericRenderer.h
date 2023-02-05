#pragma once
#include "../Renderers/GenericRenderer.h"

namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsShadow
		{
			class CShadowMapGenericRenderer : public nsRenderers::IGenericRenderer
			{
			private:
				enum class EnDescRangeType : unsigned int
				{
					enCbvForModel,
					enSrvForBoneMatrixArray,
					enSrvForWorldMatrixArray,
					enNumDescRangeTypes
				};
				enum class EnRootParameterType : unsigned int
				{
					enModel,
					enBoneMatrixArray,
					enWorldMatrixArray,
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
					return L"ShadowMapGenericRenderer";
				}

				inline void CreateSampler(
					std::vector<CD3DX12_STATIC_SAMPLER_DESC>* pSamplerDescs) const noexcept override
				{
					return;
				}


				bool CreateShader(
					nsDx12Wrappers::CBlob* pVsBlob,
					nsDx12Wrappers::CBlob* pPsBlob
				) const noexcept override;

				void CreateInputLayout(
					std::vector<D3D12_INPUT_ELEMENT_DESC>* pInputLayout) const noexcept override;

				inline std::wstring CreatePipelineStateName() const noexcept override
				{
					return L"ShadowMapGenericRenderer";
				}

			public:
				constexpr CShadowMapGenericRenderer() = default;
				virtual ~CShadowMapGenericRenderer() = default;


			private:

			};

		}
	}
}