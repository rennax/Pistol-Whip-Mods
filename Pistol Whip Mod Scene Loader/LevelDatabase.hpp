#ifndef LEVELDATABASE_HPP
#define LEVELDATABASE_HPP
extern "C" { // name mangle 
#include <funchook.h>
}

#include "il2cpp_utils.hpp"


namespace LevelDatabase {

	void initHooks(funchook_t* funchookp);


	Il2CppObject* GetLevelData(Il2CppObject* levelDatabase);
	void LevelCount(Il2CppObject* levelDatabase);
	void DublicateLevelLastLevel(Il2CppObject* levelDatabase);
};



#endif // !LEVELDATABASE_HPP
