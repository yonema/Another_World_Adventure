#include "YonemaEnginePreCompile.h"
#include "LogParts.h"

namespace nsAWA {

	namespace nsGameLog {

		namespace {

			const CVector2 kDispNormalPosition = { 0.0f,50.0f };	//表示座標
			const CVector2 kDispStartPosition = { -24.0f,50.0f };	//開始時表示座標
			constexpr float kAddTextPosition = 20.0f;			//加算座標
			constexpr float kAddTextPositionSpeed = 120.0f;		//加算速度
			constexpr float kDispTime = 5.0f;					//表示時間
			constexpr float kFontScale = 0.4f;					//フォントのサイズ
			constexpr float kFontAlphaValueAddSpeed = 0.5f;		//フォントが現れる速度(s)
		}

		void CLogParts::Create(const std::wstring& text) {

			//テキスト詳細を設定。
			SFontParameter fontParam;
			fontParam.text = text;
			fontParam.position = kDispStartPosition;
			fontParam.pivot.x = 0.0f;
			fontParam.pivot.y = 0.0f;
			fontParam.color = nsMath::CVector4::Red();
			fontParam.anchor = EnAnchors::enTopLeft;
			m_fontRenderer = NewGO<CFontRenderer>();

			//通常座標を設定。
			m_nextPosition = kDispNormalPosition;

			//初期化。
			m_fontRenderer->Init(fontParam);

			//フォントサイズを設定。
			m_fontRenderer->SetScale(kFontScale);

			//表示時間を設定。
			m_dispTimer = kDispTime;
		}
		void CLogParts::OnDestroy() {

			//フォントレンダラーを破棄。
			DeleteGO(m_fontRenderer);
			m_fontRenderer = nullptr;
		}

		void CLogParts::Release() {
			
			//自身を破棄。
			DeleteGO(this);
		}

		void CLogParts::Update(float deltaTime) {

			//タイマーを更新。
			m_dispTimer -= deltaTime;

			//タイマーが0になったら。
			if (m_dispTimer < 0.0f) {

				//表示終了。
				m_isEnd = true;
			}

			//透過度を更新。
			//CVector4 fontColor = m_fontRenderer->GetColor();
			//if (fontColor.w < 1.0f) {
			//
			//	fontColor.w += (1.0f / kFontAlphaValueAddSpeed) * deltaTime;
			//	m_fontRenderer->SetColor(fontColor);
			//}

			//座標を更新。
			CVector2 position = m_fontRenderer->GetPosition();

			if (fabsf(m_nextPosition.y - position.y) > FLT_EPSILON) {

				position.y += kAddTextPositionSpeed * deltaTime;

				if (m_nextPosition.y < position.y) {

					position.y = m_nextPosition.y;
				}

				m_fontRenderer->SetPosition(position);
			}

			if (fabsf(m_nextPosition.x - position.x) > FLT_EPSILON) {

				position.x += kAddTextPositionSpeed * deltaTime;

				if (m_nextPosition.x < position.x) {

					position.x = m_nextPosition.x;
				}

				m_fontRenderer->SetPosition(position);
			}
		}

		void CLogParts::AddPosition() {

			//目標座標を加算。
			m_nextPosition.y += kAddTextPosition;
		}
	}
}