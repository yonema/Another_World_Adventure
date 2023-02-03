#pragma once
#include "../Renderers/GenericRenderer.h"
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsSprites
		{
			class CSpriteGenericRenderer : public nsRenderers::IGenericRenderer
			{
			private:
				enum class EnDescRangeType : unsigned int
				{
					enCbvForSpriteData,
					enSrvForSceneTexture,
					enNumDescRangeTypes
				};
				enum class EnRootParameterType : unsigned int
				{
					enSpriteData,
					enSceneTexture,
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
					return L"SpriteGenericRenderer";
				}

				inline void CreateSampler(
					std::vector<CD3DX12_STATIC_SAMPLER_DESC>* pSamplerDescs) const noexcept override
				{
					pSamplerDescs->resize(1);
					pSamplerDescs->at(0).Init(
						0,
						D3D12_FILTER_ANISOTROPIC,
						D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
						D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
						D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
						0,
						16,
						D3D12_COMPARISON_FUNC_NEVER,	// ƒŠƒTƒ“ƒvƒŠƒ“ƒO‚µ‚È‚¢
						D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK,
						0.0f,
						D3D12_FLOAT32_MAX,
						D3D12_SHADER_VISIBILITY_PIXEL
					);
				}


				bool CreateShader(
					nsDx12Wrappers::CBlob* pVsBlob,
					nsDx12Wrappers::CBlob* pPsBlob
				) const noexcept override;

				void CreateInputLayout(
					std::vector<D3D12_INPUT_ELEMENT_DESC>* pInputLayout) const noexcept override;

				inline std::wstring CreatePipelineStateName() const noexcept override
				{
					return L"SpriteGenericRenderer";
				}

				inline void CreateDepthStencilState(
					D3D12_DEPTH_STENCIL_DESC* pDepthStencilState,
					DXGI_FORMAT* pDSVFormat
				) const noexcept override
				{
					pDepthStencilState->DepthEnable = FALSE;
					pDepthStencilState->DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
					pDepthStencilState->DepthFunc = D3D12_COMPARISON_FUNC_LESS;
					pDepthStencilState->StencilEnable = FALSE;
					*pDSVFormat = DXGI_FORMAT_D32_FLOAT;
					return;
				}

			public:
				constexpr CSpriteGenericRenderer() = default;
				virtual ~CSpriteGenericRenderer() = default;

			private:

			};
		}
	}
}
