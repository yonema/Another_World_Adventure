#pragma once
#include "ActiveSkill.h"

namespace nsAWA {

	namespace nsSkill {

		//アクティブスキルのデータ
		struct SActiveSkillData {

			std::string type = "NoType";	//スキルタイプ
			std::string name = "NoName";	//名前
			std::string animFilePath = "NoPath";	//アニメーションのファイルパス
			float useMP = 0.0f;				//消費MP
			std::string effectName = "NoPath";	//エフェクトの名前
			std::list<CActiveSkill::SActiveSkillAnimData> animDataList;	//アニメーションデータリスト
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

			constexpr const auto& GetActiveSkillList() const noexcept
			{
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