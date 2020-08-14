#ifndef DEBUG_HPP
#define DEBUG_HPP
#include "il2cpp_utils.hpp"
extern "C" { // name mangle 
#include <funchook.h>
}

class Debug
{
public:
	Debug();
	~Debug();
	static void initHooks(funchook_t* funchookp);
private:

};


#endif // DEBUG_HPP