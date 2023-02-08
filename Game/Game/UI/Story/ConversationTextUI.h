#pragma once

namespace nsAWA
{
	namespace nsUI
	{
		class CConversationTextUI
		{
        public:
            /**
             * @brief 初期化
             * @param conversationCSVPath 読み込む会話のCSVファイル
            */
            void Init(const wchar_t* conversationCSVPath);

            /**
             * @brief アップデート処理
             * @param deltaTime 経過時間
            */
            void Update(float deltaTime);

            /**
             * @brief 次へ(文が表示しきっていない場合すべて表示、表示しきっている場合次の文へ)
            */
            void Next();

            /**
             * @brief 初期化されている?
             * @return 
            */
            bool IsInited()
            {
                return m_isInited;
            }

        private:
            /**
             * @brief 会話のCSVデータを読み込む
             * @param conversationCSVPath 
            */
            void LoadCSVData(const wchar_t* conversationCSVPath);

            /**
             * @brief 次の文をセットする
             * @param firstLineString 
             * @param secondLineString 
            */
            void NewString(std::wstring firstLineString, std::wstring secondLineString);

            /**
             * @brief 次の文字を表示する
            */
            void ShowNextChar();

            /**
             * @brief 次の文を表示し始める
            */
            void ShowNextSentence();

            /**
             * @brief 次の文を読み込む
            */
            void HandleNextSentence();

            /**
             * @brief 空白文字扱いとしているアスタリスクを空白に変換する
             * @param showLine 表示予定の文
             * @return 変換された文
            */
            std::string ReplaceEmpty(std::string showLine);

            /**
             * @brief 一文の終わりまで一気に表示する
            */
            void SkipToEnd();

        private:
            //定数
            const CVector2 m_kTextPivot = CVector2(0.0f, 0.5f);                 //テキストのピボット
            const CVector2 m_kNamePosition = CVector2(-510.0f, 130.0f);         //名前の座標
            const CVector2 m_kFirstLinePosition = CVector2(-490.0f, 220.0f);    //一行目の文の座標
            const CVector2 m_kSecondLinePosition = CVector2(-490.0f, 275.0f);   //二行目の文の座標
            const float m_kSentenceScale = 0.75f;                               //文の拡大率


            bool m_isInited = false;                                //初期化済み?

            CFontRenderer* m_nameRenderer = nullptr;                //名前のレンダラー
            CFontRenderer* m_firstLineRenderer = nullptr;           //一行目のレンダラー
            CFontRenderer* m_secondLineRenderer = nullptr;          //二行目のレンダラー
            std::wstring m_firstLineString = L"";                   //一行目に表示する文
            std::wstring m_secondLineString = L"";                  //二行目に表示する文
            std::wstring m_currentStr = L"";                        //現在表示している文
            std::wstring* m_writingStrPtr = &m_firstLineString;     //現在表示しようとしている文へのポインタ
            CFontRenderer* m_writingFontPtr = nullptr;              //現在表示しようとしているレンダラーへのポインタ
            std::wstring::iterator itr;                             //現在表示しようとしている文のイテレーター
            float m_time = 0.0f;                                    //前回文字を追加してからの経過時間
            bool m_isShowAllLine = false;                           //すべての文字を表示し終わった?
            std::list<std::vector<std::string>> m_conversationData; //CSVから読み込んだ会話データ
            std::list<std::vector<std::string>>::iterator m_strItr; //会話データのイテレーター
		};
	}
}

