#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include "il2cpp_functions.hpp"
#include "il2cpp_utils.hpp"

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


#define DEFINE_MEMBER_CHECKER(member) \
    template<typename T, typename U, typename Enable = void> \
    struct has_ ## member : std::false_type { }; \
    template<typename T, typename U> \
    struct has_ ## member<T, U, \
        typename std::enable_if_t< \
            std::is_same_v<decltype(T::member), U>> \
        > : std::true_type { };

// Logs error and RETURNS argument 1 IFF argument 2 boolean evaluates as false; else EVALUATES to argument 2
// thank god for this GCC ({}) extension which "evaluates to the last statement"
#define RET_UNLESS(retval, expr) ({ \
    const auto& __temp__ = expr; \
    if (!__temp__) { \
        LOG("ERROR, %s (in %s at %s:%i) returned false!", #expr, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
        return retval; \
    } \
    __temp__; \
})
#define RET_V_UNLESS(expr) RET_UNLESS(, expr)
#define RET_0_UNLESS(expr) RET_UNLESS(0, expr)

#endif // !UTILS_H
