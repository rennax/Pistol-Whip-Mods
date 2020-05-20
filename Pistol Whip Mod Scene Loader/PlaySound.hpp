#ifndef PLAYSOUND_HPP
#define PLAYSOUND_HPP
extern "C" { // name mangle 
#include <funchook.h>
}

// Namespace: Valve.VR.InteractionSystem
namespace ValvePlaySound {
	void initHooks(funchook_t* funchookp);
};

#endif // !PLAYSOUND_HPP
