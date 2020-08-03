#ifndef PLAYERACTIONMANAGER_HPP
#define PLAYERACTIONMANAGER_HPP
#include "il2cpp_utils.hpp"
extern "C" {
#include <funchook.h>
}


class PlayerActionManager
{
public:
	PlayerActionManager();
	~PlayerActionManager();
	static void initHooks(funchook_t* funchookp);
private:

};

#endif // PLAYERACTIONMANAGER_HPP