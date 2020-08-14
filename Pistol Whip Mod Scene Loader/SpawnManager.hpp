#ifndef SPAWNMANAGER_HPP
#define SPAWNMANAGER_HPP
#include "il2cpp_utils.hpp"
extern "C" { // name mangle 
#include <funchook.h>
}

class SpawnManager
{
public:
	SpawnManager();
	~SpawnManager();
	static void initHooks(funchook_t* funchookp);
private:

};


#endif // !SPAWNMANAGER_HPP
