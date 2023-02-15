#include "SceneBase.h"
namespace nsAWA
{
	namespace nsScene
	{
		ISceneBase* ISceneBase::m_currentScene = nullptr;
		bool ISceneBase::m_nowCreating = false;


	}
}