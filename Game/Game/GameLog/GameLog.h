#pragma once

namespace nsAWA {

	namespace nsGameLog {

		class CLogParts;

		//�Q�[�����O�N���X
		class CGameLog : nsUtils::SNoncopyable
		{
		public:
			static CGameLog* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CGameLog* instance = new CGameLog;

				//�C���X�^���X�����^�[���B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void AddGameLog(const std::string& text);

			void Update(float deltaTime);

		private:
			std::list<CLogParts*> m_logParts;		//���O���i���X�g
		};
	}
}