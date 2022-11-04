#include "FBXGenericRenderer.h"
#include "../GameWindow/MessageBox.h"
#include "../GraphicsEngine.h"

namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace nsFBXModels
		{
			const wchar_t* const CFBXGenericRenderer::m_kVsFilePath =
				L"Assets/Shaders/FbxTestVertexShader.hlsl";
			const char* const CFBXGenericRenderer::m_kVsEntryFuncName = "VSMain";
			const wchar_t* const CFBXGenericRenderer::m_kPsFilePath =
				L"Assets/Shaders/FbxTestPixelShader.hlsl";
			const char* const CFBXGenericRenderer::m_kPsEntryFuncName = "PSMain";

			bool CFBXGenericRenderer::Init()
			{
				auto device = CGraphicsEngine::GetInstance()->GetDevice();
				if (CreateRootSignature(device) != true)
				{
					return false;
				}
				if (CreatePipelineState(device) != true)
				{
					return false;
				}

				return true;
			}


			bool CFBXGenericRenderer::CreateRootSignature(ID3D12Device5* device)
			{
				int numCBVs = 0;
				int numSRVs = 0;

				constexpr unsigned int kNumDescTblRanges = 
					static_cast<unsigned int>(EnDescRangeType::enNumDescRangeTypes);
				constexpr unsigned int kCbvForModelDataDescRangeNo =
					static_cast<unsigned int>(EnDescRangeType::enCbvForModelData);
				constexpr unsigned int kCbvForMaterialDataDescRangeNo =
					static_cast<unsigned int>(EnDescRangeType::enCbvForMaterialData);
				constexpr unsigned int kSrvForMaterialDataDescRangeNo =
					static_cast<unsigned int>(EnDescRangeType::enSrvForMaterialData);

				CD3DX12_DESCRIPTOR_RANGE1 descTblRanges[kNumDescTblRanges] = {};
				descTblRanges[kCbvForModelDataDescRangeNo].Init(
					D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, numCBVs++);
				descTblRanges[kCbvForMaterialDataDescRangeNo].Init(
					D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, numCBVs++);
				descTblRanges[kSrvForMaterialDataDescRangeNo].Init(
					D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, numSRVs++);


				constexpr unsigned int kNumRootParameters = 
					static_cast<unsigned int>(EnRootParameterType::enNumRootParamerterTypes);
				constexpr unsigned int kModelDataRootParamNo =
					static_cast<unsigned int>(EnRootParameterType::enModelData);
				constexpr unsigned int kMaterialDataRootParamNo =
					static_cast<unsigned int>(EnRootParameterType::enMaterialData);

				CD3DX12_ROOT_PARAMETER1 rootParameters[kNumRootParameters] = {};
				
				// ワールド・ボーン変換
				rootParameters[kModelDataRootParamNo].InitAsDescriptorTable(
					1, &descTblRanges[kCbvForModelDataDescRangeNo], D3D12_SHADER_VISIBILITY_VERTEX);
				rootParameters[kMaterialDataRootParamNo].InitAsDescriptorTable(
					2, &descTblRanges[kCbvForMaterialDataDescRangeNo], D3D12_SHADER_VISIBILITY_PIXEL);

				constexpr unsigned int kNumSamplers =
					static_cast<unsigned int>(EnSamplerType::enNumSamplerTypes);
				constexpr unsigned int kNormalSamplerNo =
					static_cast<unsigned int>(EnSamplerType::enNormal);

				CD3DX12_STATIC_SAMPLER_DESC samplerDescs[kNumSamplers] = {};
				samplerDescs[kNormalSamplerNo].Init(
					0,
					D3D12_FILTER_ANISOTROPIC,
					D3D12_TEXTURE_ADDRESS_MODE_WRAP,
					D3D12_TEXTURE_ADDRESS_MODE_WRAP,
					D3D12_TEXTURE_ADDRESS_MODE_WRAP,
					0,
					16,
					D3D12_COMPARISON_FUNC_NEVER,	// リサンプリングしない
					D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK,
					0.0f,
					D3D12_FLOAT32_MAX,
					D3D12_SHADER_VISIBILITY_PIXEL
				);

				auto res = GetRootSignature()->Init(
					kNumRootParameters,
					rootParameters,
					kNumSamplers,
					samplerDescs,
					// 頂点情報（入力アセンブラ）がある。
					D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS,
					L"PMDModel"
				);

				return res;
			}

			bool CFBXGenericRenderer::CreatePipelineState(ID3D12Device5* device)
			{
				nsDx12Wrappers::CBlob vsBlob;
				nsDx12Wrappers::CBlob psBlob;

				auto res = LoadShader(
					m_kVsFilePath,
					m_kVsEntryFuncName,
					&vsBlob,
					m_kPsFilePath,
					m_kPsEntryFuncName,
					&psBlob
				);
				if (res != true)
				{
					return false;
				}

				constexpr D3D12_INPUT_ELEMENT_DESC inputLayout[] =
				{
					{
						"POSITION",
						0,
						DXGI_FORMAT_R32G32B32_FLOAT,
						0,
						D3D12_APPEND_ALIGNED_ELEMENT,
						D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
						0
					},
					{
						"NORMAL",
						0,
						DXGI_FORMAT_R32G32B32_FLOAT,
						0,
						D3D12_APPEND_ALIGNED_ELEMENT,
						D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
						0
					},
					{
						"COLOR",
						0,
						DXGI_FORMAT_R32G32B32A32_FLOAT,
						0,
						D3D12_APPEND_ALIGNED_ELEMENT,
						D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
						0
					},
					{
						"TEXCOORD",	// UV
						0,
						DXGI_FORMAT_R32G32_FLOAT,
						0,
						D3D12_APPEND_ALIGNED_ELEMENT,
						D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
						0
					},
				};

				D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
				pipelineDesc.pRootSignature = GetRootSignature()->Get();
				pipelineDesc.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
				pipelineDesc.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
				pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

				pipelineDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

				pipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
				pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;

				pipelineDesc.DepthStencilState.DepthEnable = true;
				pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
				pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
				pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
				pipelineDesc.DepthStencilState.StencilEnable = false;

				pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
				pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

				pipelineDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
				pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

				pipelineDesc.NumRenderTargets = 1;
				pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

				// AAしない設定
				pipelineDesc.SampleDesc.Count = 1;
				pipelineDesc.SampleDesc.Quality = 0;

				pipelineDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
				res = GetPipelineState()->InitAsGraphicsPipelineState(pipelineDesc, L"FBXModel");

				return res;
			}


		}
	}
}