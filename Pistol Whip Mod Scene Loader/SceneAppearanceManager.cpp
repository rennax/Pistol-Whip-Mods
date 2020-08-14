#include "SceneAppearanceManager.hpp"
#include "List.hpp"
#include "utils.h"

bool SceneAppearanceManager::overwriteOnLevelSelect = false;

MAKE_HOOK(OnLevelSelect, void, void* self, Il2CppObject* e)
{
	LOG("Messages.LevelSelectEvent sent and received by SceneAppearanceManger\n");
	if (!SceneAppearanceManager::overwriteOnLevelSelect)
	{
		return OnLevelSelect_orig(self, e);
	}
	return OnLevelSelect_orig(self, e);
	Il2CppObject* map = il2cpp_utils::GetFieldValue(e, "level"); //GameMap
	Il2CppObject* level = il2cpp_utils::GetFieldValue(map, "data"); //LevelData
	CSharp::List<Il2CppObject*> sections(il2cpp_utils::GetFieldValue(level, "sections"));
	uint32_t count = sections.Count();
	if (count <= 0)
	{
		LOG("WARNING sections.count <= 0, we terminate instead of throwing error\n");
		exit(-1);
	}
	Il2CppObject* section = sections[0];
	Color mainColor;
	il2cpp_utils::RunMethod(&mainColor, section, "get_mainColor");
	bool scaleFog;
	il2cpp_utils::RunMethod(&scaleFog, section, "get_scaleFog");

	Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "Messages/SceneColorEvent");
	Il2CppObject* msg = il2cpp_functions::object_new(klass);
	il2cpp_utils::RunMethod(msg, ".ctor", &mainColor, &scaleFog);

	klass = il2cpp_utils::GetClassFromName("", "Messenger");
	Il2CppObject* messenger = nullptr;
	il2cpp_utils::RunMethod(&messenger, klass, "get_Default");
	LOG("Attempting to run Send(Messages.SceneColorEvent e)\n");
	const MethodInfo* info = il2cpp_utils::GetMethod("", "Messenger", "Send", 1);
	// Get my generic methodInfo
	info = il2cpp_utils::MakeGeneric(info, { il2cpp_utils::GetClassFromName("", "Messages/SceneColorEvent") });
	// Call the method
	if (!il2cpp_utils::RunMethod(messenger, info, msg))
		LOG("WARNING: Failed to run Send(Messages.SceneColorEvent e)\n");

}



SceneAppearanceManager::SceneAppearanceManager()
{
}

SceneAppearanceManager::~SceneAppearanceManager()
{
}

void SceneAppearanceManager::initHooks(funchook_t* funchookp)
{
	//OnLevelSelect_orig = (OnLevelSelect_t)il2cpp_utils::GetMethod("", "SceneAppearanceManager", "OnLevelSelect", 1)->methodPointer;
	//INSTALL_HOOK(OnLevelSelect);

}
