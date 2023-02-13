#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        enum class EnSelectingItem
        {
            enRest,
            enSave
        };

        class CInnWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

            bool IsEnd()
            {
                return m_endFlag;
            }
        public:
            CInnWindowUI() = default;
            ~CInnWindowUI() = default;

            void RegisterAnimationEvents();
            
            void ChengeSelectingItem();

            void ExitUI();

            void StartExecute();

            void Execute();
        private: // constant data member
            const char* m_kInnWindowFilePath = "Assets/Level2D/LevelFiles/InnUI.tdl";
        private: // data member
            nsLevel2D::CLevel2D m_level;

            EnSelectingItem m_selecting = EnSelectingItem::enRest;  //�I�𒆂̍���
            bool m_playingAnimation = false;                        //�A�j���[�V�������o��?
            bool m_endFlag = false;
        };
    }
}