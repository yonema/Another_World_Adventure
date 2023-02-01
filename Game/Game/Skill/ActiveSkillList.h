#pragma once

namespace nsAWA {

	namespace nsSkill {

		//前方宣言
		class CActiveSkill;

		//アクティブスキルのデータ
		struct SActiveSkillData {

			std::string type = "NoType";	//スキルタイプ
			std::string name = "NoName";	//名前
			float useMP = 0.0f;				//消費MP
		};

		//アクティブスキルのリスト
		class CActiveSkillList : nsUtils::SNoncopyable
		{
		public:
			static CActiveSkillList* GetInstance() {

				//インスタンスを生成。
				static CActiveSkillList* activeSkillList = new CActiveSkillList;

				return activeSkillList;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadActiveSkillList();

			const SActiveSkillData& GetActiveSkillData(const std::string& activeSkillName);

			const std::list<SActiveSkillData>& GetActiveSkillData() {

				//アクティブスキルのリストを取得。
				return m_activeSkillList;
			}

		private:
			void AddActiveSkill(const SActiveSkillData& activeSkillData) {

				//アクティブスキルをリストに追加。
				m_activeSkillList.emplace_back(activeSkillData);
			}

		private:
			std::list<SActiveSkillData> m_activeSkillList;		//アクティブスキルのリスト
		};

		//アクティブスキル生成クラス
		class CActiveSkillBuilder : nsUtils::SNoncopyable {

		public:
			CActiveSkill* CreateActiveSkill(const std::string& activeSkillName);
		};
	}
}