#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
extern "C" {
#include <funchook.h>
}

namespace LevelManager {
	void* levelManager();
	void initHooks(funchook_t* funchookp);
};

#endif