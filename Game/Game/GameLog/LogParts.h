#pragma once

namespace nsAWA {

	namespace nsGameLog {

		//ログ部品クラス
		class CLogParts : public IGameObject
		{
		public:
			void Create(const std::wstring& text, const CVector4& fontColor);

			void OnDestroy()override final;

			void Release();

			void Update(float deltaTime);

			void AddPosition();

			bool IsEnd()const {

				//表示が終わった？
				return m_isEnd;
			}
		private:
			CFontRenderer* m_fontRenderer = nullptr;	//フォントレンダラー
			float m_dispTimer = 0.0f;					//表示時間のタイマー
			bool m_isEnd = false;						//表示が終わった？
			CVector2 m_nextPosition = CVector2::Zero();	//次の座標
		};
	}
}