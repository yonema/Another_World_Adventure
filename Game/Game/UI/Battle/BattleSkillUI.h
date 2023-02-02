#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSkillIconUI;

        class CBattleSkillUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CBattleSkillUI() = default;
            ~CBattleSkillUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UI�̃A�j���[�V����

        private: // constant data member
            static const int m_kSkillIconMaxNum = 6; // �X�L���A�C�R���̌�

        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSkillIconUI* m_skillIconUI[m_kSkillIconMaxNum] = { nullptr };
        };

    }
}