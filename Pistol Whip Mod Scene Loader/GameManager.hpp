#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
extern "C" { // name mangle 
#include <funchook.h>
}



//Pistol Whip GameManager : Singleton<GameManager>
namespace GameManager {

	void initHooks(funchook_t* funchookp);
};



#endif // !GAMEMANAGER_HPP