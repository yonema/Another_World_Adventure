#include "TransSpriteGenericRenderer.h"
namespace nsYMEngine
{
	namespace nsGraphics
	{
		namespace ns2D
		{
			void CTransSpriteGenericRenderer::OverrideGraphicsPipelineStateDesc(
				D3D12_GRAPHICS_PIPELINE_STATE_DESC* pPipelineDesc)
			{
				// 半透明合成用の設定で上書き
				pPipelineDesc->BlendState.RenderTarget[0].BlendEnable = true;
				pPipelineDesc->BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
				pPipelineDesc->BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
				pPipelineDesc->BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;

				return;
			}
		}
	}
}