#pragma once

// note: �A�C�e�����X�g�Ɖ摜�\���̏����͊��S�ɕ������Ă�̂�
//       �A�C�e�����X�g�őI�����Ă���̂ƁA��ʏ��UI�������o�O����������\������

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CItemUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CItemUI() = default;
            ~CItemUI() = default;

        public:
            void LoadLevel();

            void LoadImgData(const int itemIconNum, const nsLevel2D::SLevel2DSpriteData& imgData);

            void LoadItemIconSprite();

            const int SearchItemName(std::string& name);

        private:
            void Animation(); // UI�̃A�j���[�V����


        public:
            void MoveNextItemUI();

            void MoveBackItemUI();


        public:
            void ActiveDrawing();

            void DeactiveDrawing();


        private: // enum
            enum class EnItemIcon
            {
                enCenter,
                enNext,
                enBack,
                enNotFound,
                enMaxItemIcon
            };


        private: // struct
            struct SItemIconInitialData
            {
                CVector2 position;
                float rotateDeg = 0.0f;
                CVector2 scale;
                CVector2 spriteSize;
                CVector2 pivot;
                int priority = 0;
            };

            SItemIconInitialData m_itemIconInitialData[static_cast<int>(EnItemIcon::enMaxItemIcon)];

            struct SItemIconSpriteData
            {
                CSpriteUI* sprite = nullptr;

                EnItemIcon itemIconPos = EnItemIcon::enNotFound;
            };

            std::vector<SItemIconSpriteData> m_itemIconSpriteData;


        private: // constant member
            static const char* m_kLevel2DFilePath;

            static const char* m_kItemBaseSpriteFilePath;

            static const char* m_kPotionSpriteFilePath;

            static const char* m_kTestSpriteFilePath[5];



        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteBase = nullptr;
            CSpriteUI* m_spriteItemIcon = nullptr;

            std::vector<CSpriteUI*> m_vecSpriteItemIcon;

            std::list<CSpriteUI*>  m_listSpriteItemIcon;

            int m_spriteItemIconNum = 0;

            bool m_flagDrawSprite = false;

            CVector2 m_initialPosition[static_cast<int>(EnItemIcon::enMaxItemIcon)] =
            {
                CVector2::Zero(),
                CVector2::Zero(),
                CVector2::Zero(),
                CVector2::Zero()
            };

        };
    }
}