#pragma once

namespace nsAWA {

	namespace nsItem {

		//�A�C�e���N���X
		class CItem : nsUtils::SNoncopyable
		{
		public:
			void Create();

			void Release();
		private:
			CModelRenderer* m_itemModel = nullptr;	//���f��
		};
	}
}

