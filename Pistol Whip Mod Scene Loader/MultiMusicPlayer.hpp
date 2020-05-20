#ifndef MULTIMUSICPLAYER_HPP
#define MULTIMUSICPLAYER_HPP
extern "C" { // name mangle 
#include <funchook.h>
}

// Namespace: SonicBloom.Koreo.Players
namespace MultiMusicPlayer {
	void initHooks(funchook_t* funchookp);
};

#endif // !MULTIMUSICPLAYER_HPP
