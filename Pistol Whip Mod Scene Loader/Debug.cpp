#include "Debug.hpp"

#include "utils.h"


Debug::Debug()
{
}

Debug::~Debug()
{
}

MAKE_HOOK(Log, void, Il2CppObject* message) {
	Il2CppString* str = reinterpret_cast<Il2CppString*>(message);
	LOG("Debug.Log: %s\n", to_utf8(csstrtostr(str)).c_str());
	return Log_orig(message);
}

MAKE_HOOK(LogError, void, Il2CppObject* message) {
	Il2CppString* str = reinterpret_cast<Il2CppString*>(message);
	LOG("Debug.Error: %s\n", to_utf8(csstrtostr(str)).c_str());
	return LogError_orig(message);
}

MAKE_HOOK(LogWarning, void, Il2CppObject* message) {
	Il2CppString* str = reinterpret_cast<Il2CppString*>(message);
	LOG("Debug.Warning: %s\n", to_utf8(csstrtostr(str)).c_str());
	return LogError_orig(message);
}

void Debug::initHooks(funchook_t* funchookp)
{
	Log_orig = (Log_t)il2cpp_utils::GetMethod("UnityEngine", "Debug", "Log", 1)->methodPointer;
	INSTALL_HOOK(Log);

	LogError_orig = (LogError_t)il2cpp_utils::GetMethod("UnityEngine", "Debug", "LogError", 1)->methodPointer;
	INSTALL_HOOK(LogError);

	LogWarning_orig = (LogWarning_t)il2cpp_utils::GetMethod("UnityEngine", "Debug", "LogWarning", 1)->methodPointer;
	INSTALL_HOOK(LogWarning);
}
