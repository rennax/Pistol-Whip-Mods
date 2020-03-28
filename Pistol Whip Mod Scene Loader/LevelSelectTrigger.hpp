#ifndef LEVELSELECTTRIGGER_HPP
#define LEVELSELECTTRIGGER_HPP
extern "C" { // name mangle 
#include <funchook.h>
}

#include <functional>

//Pistol Whip GameManager : Singleton<GameManager>
namespace LevelSelectTrigger {
	using OnLevelSelectCallable = std::function<void(void * gameMap)>;
	static void* onLevelSelect = nullptr;

	void initHooks(funchook_t* funchookp);
};



#endif // !LEVELSELECTTRIGGER_HPP