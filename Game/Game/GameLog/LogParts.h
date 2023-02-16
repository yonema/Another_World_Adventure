#pragma once

namespace nsAWA {

	namespace nsGameLog {

		//���O���i�N���X
		class CLogParts : public IGameObject
		{
		public:
			void Create(const std::wstring& text, const CVector4& fontColor);

			void OnDestroy()override final;

			void Release();

			void Update(float deltaTime);

			void AddPosition();

			bool IsEnd()const {

				//�\�����I������H
				return m_isEnd;
			}
		private:
			CFontRenderer* m_fontRenderer = nullptr;	//�t�H���g�����_���[
			float m_dispTimer = 0.0f;					//�\�����Ԃ̃^�C�}�[
			bool m_isEnd = false;						//�\�����I������H
			CVector2 m_nextPosition = CVector2::Zero();	//���̍��W
		};
	}
}