#pragma once

namespace nsAWA {

	namespace nsItem {

		//アイテムクラス
		class CItem : nsUtils::SNoncopyable
		{
		public:
			void Create();

			void Release();
		private:
			CModelRenderer* m_itemModel = nullptr;	//モデル
		};
	}
}

