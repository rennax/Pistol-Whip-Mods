#ifndef UTILS_H
#define UTILS_H

//Example of what MAKE_HOOK creates
//static void (*sceneManagerLoadScene_orig)(void* self, void* sceneName, void* loadSceneMode);
//typedef void (*sceneManagerLoadScene)(void* self, void* sceneName, void* loadSceneMode);
//static void sceneManagerLoadScene_hook(void* self, void* sceneName, void* loadSceneMode)

//#define MAKE_HOOK(name, retval, ...) \
//static retval name ## _hook(__VA_ARGS__)

#define MAKE_HOOK(name, retval, ...) \
static retval (*name ## _orig)(__VA_ARGS__);\
typedef retval (*name##_t)(__VA_ARGS__);\
static retval name ## _hook(__VA_ARGS__)

#define STRING(x) #x
#define INSTALL_HOOK(name) \
LOG("Installing hook" #name ", at address: %p\n", name ## _orig);\
funchook_prepare(funchookp, (void**)&name ## _orig, name ## _hook);\

#endif // !UTILS_H
