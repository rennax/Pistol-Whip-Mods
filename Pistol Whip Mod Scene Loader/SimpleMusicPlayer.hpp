#ifndef SIMPLEMUSICPLAYER_HPP
#define SIMPLEMUSICPLAYER_HPP
extern "C" { // name mangle 
#include <funchook.h>
}

// Namespace: SonicBloom.Koreo.Players
namespace SimpleMusicPlayer {
	void initHooks(funchook_t* funchookp);
};

#endif // !SIMPLEMUSICPLAYER_HPP
