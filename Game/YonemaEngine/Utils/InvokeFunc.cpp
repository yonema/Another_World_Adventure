#include "InvokeFunc.h"
namespace nsYMEngine
{
	namespace nsUtils
	{
		CInvokeFunc* CInvokeFunc::m_instance = nullptr;

		void CInvokeFunc::Update(float deltaTime)
		{
			m_invokeFuncList.remove_if(
				[&](SInvokeFuncData& invokeFuncData)
				{
					if (invokeFuncData.CountTime(deltaTime))
					{
						invokeFuncData.func();
						return true;
					}
					return false;
				}
			);

			return;
		}


	}
}