#include "SceneManager.hpp"
#include "logger.h"
#include "il2cpp_utils.hpp"
#include "utils.h"

namespace SceneManager {

MAKE_HOOK(LoadScene, void, void* self, void* sceneName, void* loadSceneMode)
{
	LOG("UnityEngine.SceneManagement::SceneManager::LoadScene() hook called\n");
	LoadScene_orig(self, sceneName, loadSceneMode);

}

void initHooks(funchook_t* funchookp)
{
	LoadScene_orig = (LoadScene_t)il2cpp_utils::GetMethod("UnityEngine.SceneManagement", "SceneManager", "LoadScene", 2)->methodPointer;
	INSTALL_HOOK(LoadScene);
}


};
