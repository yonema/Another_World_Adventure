#include "YonemaEnginePreCompile.h"
#include "LogParts.h"

namespace nsAWA {

	namespace nsGameLog {

		namespace {

			const CVector2 kDispNormalPosition = { 0.0f,50.0f };	//�\�����W
			const CVector2 kDispStartPosition = { -24.0f,50.0f };	//�J�n���\�����W
			constexpr float kAddTextPosition = 20.0f;			//���Z���W
			constexpr float kAddTextPositionSpeed = 120.0f;		//���Z���x
			constexpr float kDispTime = 5.0f;					//�\������
			constexpr float kFontScale = 0.4f;					//�t�H���g�̃T�C�Y
			constexpr float kFontAlphaValueAddSpeed = 0.5f;		//�t�H���g������鑬�x(s)
		}

		void CLogParts::Create(const std::wstring& text) {

			//�e�L�X�g�ڍׂ�ݒ�B
			SFontParameter fontParam;
			fontParam.text = text;
			fontParam.position = kDispStartPosition;
			fontParam.pivot.x = 0.0f;
			fontParam.pivot.y = 0.0f;
			fontParam.color = nsMath::CVector4::Red();
			fontParam.anchor = EnAnchors::enTopLeft;
			m_fontRenderer = NewGO<CFontRenderer>();

			//�ʏ���W��ݒ�B
			m_nextPosition = kDispNormalPosition;

			//�������B
			m_fontRenderer->Init(fontParam);

			//�t�H���g�T�C�Y��ݒ�B
			m_fontRenderer->SetScale(kFontScale);

			//�\�����Ԃ�ݒ�B
			m_dispTimer = kDispTime;
		}
		void CLogParts::OnDestroy() {

			//�t�H���g�����_���[��j���B
			DeleteGO(m_fontRenderer);
			m_fontRenderer = nullptr;
		}

		void CLogParts::Release() {
			
			//���g��j���B
			DeleteGO(this);
		}

		void CLogParts::Update(float deltaTime) {

			//�^�C�}�[���X�V�B
			m_dispTimer -= deltaTime;

			//�^�C�}�[��0�ɂȂ�����B
			if (m_dispTimer < 0.0f) {

				//�\���I���B
				m_isEnd = true;
			}

			//���ߓx���X�V�B
			//CVector4 fontColor = m_fontRenderer->GetColor();
			//if (fontColor.w < 1.0f) {
			//
			//	fontColor.w += (1.0f / kFontAlphaValueAddSpeed) * deltaTime;
			//	m_fontRenderer->SetColor(fontColor);
			//}

			//���W���X�V�B
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

			//�ڕW���W�����Z�B
			m_nextPosition.y += kAddTextPosition;
		}
	}
}