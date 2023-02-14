#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//アクティブスキル
		class CActiveSkill : public CSkill
		{
		public:
			//アクティブスキルのタイプ
			enum class EnActiveSkillType {

				enSword,	//剣スキル
				enAxe,		//斧スキル
				enWand,		//杖スキル
				enMagic,	//魔法スキル
				enNum,		//タイプ数

				enNone = -1//設定なし
			};

			using ActiveSkillAnimEventData = std::list<std::vector<std::string>>;

			struct SActiveSkillAnimData {

				std::string skillName = "NoName";			//スキルの名前
				std::string index = "NoIndex";				//アニメーションイベントにインデックス
				ActiveSkillAnimEventData sAnimEventData;	//アニメーションイベントデータ
			};
		public:
			void Execute();

			void SetUseMP(float useMP) {

				//消費MPを設定。
				m_useMP = useMP;
			}

			void SetType(EnActiveSkillType type) {

				//タイプの設定がおかしいなら。
				if (type == EnActiveSkillType::enNone || type > EnActiveSkillType::enNum) {
#ifdef _DEBUG
					//エラー出力。
					nsGameWindow::MessageBoxError(L"アクティブスキルのタイプ設定が不適切です。");
#endif // _DEBUG
					std::abort();
				}

				//タイプを設定。
				m_activeSkillType = type;
			}

			EnActiveSkillType GetType()const {

				//タイプを取得。
				return m_activeSkillType;
			}

			float GetUseMP()const {

				//消費MPをリターン。
				return m_useMP;
			}

			void SetAnimaitonFilePath(const std::string& animFilePath) {

				//アニメーションのファイルパスを設定。
				m_animFilePath = animFilePath;
			}

			const std::string& GetAnimationFilePath()const {

				//アニメーションのファイルパスをリターン。
				return m_animFilePath;
			}

			void SetAnimDataList(const std::list<SActiveSkillAnimData>& animDataList) {

				//アニメーションデータのリストを設定。
				m_activeSkillAnimDataList = animDataList;
			}

			void SetEffectName(const std::string& effectName) {
				
				//エフェクトの名前を設定。
				m_effectName = effectName;
			}

			const SActiveSkillAnimData& GetActiveSkillAnimData(const std::string& index)const;
		public:
			static int m_kActiveSkillNumMax;
		private:
			float m_useMP = 0.0f;	//消費MP
			std::string m_animFilePath = "NoFilePath";							//アニメーションのファイルパス
			EnActiveSkillType m_activeSkillType = EnActiveSkillType::enNone;	//アクティブスキルのタイプ
			std::string m_effectName = "NoName";						//エフェクトの名前
			std::list<SActiveSkillAnimData> m_activeSkillAnimDataList;	//アクティブスキルのアニメーションデータのリスト
		};
	}
}

