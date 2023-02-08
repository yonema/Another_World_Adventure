#pragma once

namespace nsAWA
{
	namespace nsUI
	{
		class CConversationTextUI
		{
        public:
            /**
             * @brief ������
             * @param conversationCSVPath �ǂݍ��މ�b��CSV�t�@�C��
            */
            void Init(const wchar_t* conversationCSVPath);

            /**
             * @brief �A�b�v�f�[�g����
             * @param deltaTime �o�ߎ���
            */
            void Update(float deltaTime);

            /**
             * @brief ����(�����\���������Ă��Ȃ��ꍇ���ׂĕ\���A�\���������Ă���ꍇ���̕���)
            */
            void Next();

            /**
             * @brief ����������Ă���?
             * @return 
            */
            bool IsInited()
            {
                return m_isInited;
            }

        private:
            /**
             * @brief ��b��CSV�f�[�^��ǂݍ���
             * @param conversationCSVPath 
            */
            void LoadCSVData(const wchar_t* conversationCSVPath);

            /**
             * @brief ���̕����Z�b�g����
             * @param firstLineString 
             * @param secondLineString 
            */
            void NewString(std::wstring firstLineString, std::wstring secondLineString);

            /**
             * @brief ���̕�����\������
            */
            void ShowNextChar();

            /**
             * @brief ���̕���\�����n�߂�
            */
            void ShowNextSentence();

            /**
             * @brief ���̕���ǂݍ���
            */
            void HandleNextSentence();

            /**
             * @brief �󔒕��������Ƃ��Ă���A�X�^���X�N���󔒂ɕϊ�����
             * @param showLine �\���\��̕�
             * @return �ϊ����ꂽ��
            */
            std::string ReplaceEmpty(std::string showLine);

            /**
             * @brief �ꕶ�̏I���܂ň�C�ɕ\������
            */
            void SkipToEnd();

        private:
            //�萔
            const CVector2 m_kTextPivot = CVector2(0.0f, 0.5f);                 //�e�L�X�g�̃s�{�b�g
            const CVector2 m_kNamePosition = CVector2(-510.0f, 130.0f);         //���O�̍��W
            const CVector2 m_kFirstLinePosition = CVector2(-490.0f, 220.0f);    //��s�ڂ̕��̍��W
            const CVector2 m_kSecondLinePosition = CVector2(-490.0f, 275.0f);   //��s�ڂ̕��̍��W
            const float m_kSentenceScale = 0.75f;                               //���̊g�嗦


            bool m_isInited = false;                                //�������ς�?

            CFontRenderer* m_nameRenderer = nullptr;                //���O�̃����_���[
            CFontRenderer* m_firstLineRenderer = nullptr;           //��s�ڂ̃����_���[
            CFontRenderer* m_secondLineRenderer = nullptr;          //��s�ڂ̃����_���[
            std::wstring m_firstLineString = L"";                   //��s�ڂɕ\�����镶
            std::wstring m_secondLineString = L"";                  //��s�ڂɕ\�����镶
            std::wstring m_currentStr = L"";                        //���ݕ\�����Ă��镶
            std::wstring* m_writingStrPtr = &m_firstLineString;     //���ݕ\�����悤�Ƃ��Ă��镶�ւ̃|�C���^
            CFontRenderer* m_writingFontPtr = nullptr;              //���ݕ\�����悤�Ƃ��Ă��郌���_���[�ւ̃|�C���^
            std::wstring::iterator itr;                             //���ݕ\�����悤�Ƃ��Ă��镶�̃C�e���[�^�[
            float m_time = 0.0f;                                    //�O�񕶎���ǉ����Ă���̌o�ߎ���
            bool m_isShowAllLine = false;                           //���ׂĂ̕�����\�����I�����?
            std::list<std::vector<std::string>> m_conversationData; //CSV����ǂݍ��񂾉�b�f�[�^
            std::list<std::vector<std::string>>::iterator m_strItr; //��b�f�[�^�̃C�e���[�^�[
		};
	}
}

