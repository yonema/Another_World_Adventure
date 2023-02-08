#pragma once
namespace nsAWA {

	namespace nsSkill {

		//前方宣言
		class CPassiveSkill;

		//パッシブスキルのデータ
		struct SPassiveSkillData {

			std::string name = "NoName";	//名前
			std::list<std::vector<std::string>> featureList;	//効果のリスト
		};
		//パッシブスキルリスト
		class CPassiveSkillList : nsUtils::SNoncopyable
		{
		public:
			static CPassiveSkillList* GetInstance() {

				//インスタンスを生成。
				static CPassiveSkillList* passiveSkillList = new CPassiveSkillList;

				return passiveSkillList;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadPassiveSkillList();

			const SPassiveSkillData& GetPassiveSkillData(const std::string& passiveSkillName);

		private:
			std::list<SPassiveSkillData> m_passiveSkillList;	//パッシブスキルのリスト
		};

		//パッシブスキル生成クラス
		class CPassiveSkillBuilder : nsUtils::SNoncopyable {

		public:
			CPassiveSkill* CreatePassiveSkill(const std::string& passiveSkillName);
		};
	}
}

