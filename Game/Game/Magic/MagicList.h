#pragma once

namespace nsAWA {

	namespace nsMagic {

		//前方宣言
		class CMagicBase;

		//魔法リスト
		class CMagicList : nsUtils::SNoncopyable
		{
		public:
			//魔法スキルのデータ
			struct SMagicData {

				std::string name = "NoName";	//名前
				std::string magicType = "NoType";//魔法の種類
				std::list<std::vector<std::string>> featureList;	//効果のリスト
			};

		public:
			static CMagicList* GetInstance() {

				//インスタンスを生成。
				static CMagicList* instance = new CMagicList;

				//インスタンスを取得。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadMagicList();


			const CMagicList::SMagicData& GetMagicData(const std::string& name)const;

			constexpr const auto& GetMagicList() const noexcept
			{
				//魔法スキルのリストを取得。
				return m_magicList;
			}

		private:
			std::list<SMagicData> m_magicList;	//魔法スキルのリスト
		};

		//魔法生成クラス
		class CMagicBuilder : nsUtils::SNoncopyable {

		public:
			CMagicBase* CreateMagic(const std::string& magicName);
		};
	}
}

