#ifndef SCENEAPPEARANCEMANAGER_HPP
#define SCENEAPPEARANCEMANAGER_HPP
#include "il2cpp_utils.hpp"
#include "utils-functions.hpp"
extern "C" { // name mangle 
#include <funchook.h>
}

class SceneAppearanceManager
{
public:
	SceneAppearanceManager();
	~SceneAppearanceManager();
	static void initHooks(funchook_t* funchookp);
	static bool overwriteOnLevelSelect;
private:
};


#endif // !SCENEAPPEARANCEMANAGER_HPP
