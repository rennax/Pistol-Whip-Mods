#ifndef IL2CPP_UTILS_HPP
#define IL2CPP_UTILS_HPP

#include <string_view>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <sstream>
#include "typedefs.h"
#include "il2cpp_functions.hpp"
#include "utils-functions.hpp"
#include "logger.h"


namespace il2cpp_utils
{
    namespace array_utils {
        static char* il2cpp_array_addr_with_size(Il2CppArray* array, int32_t size, uintptr_t idx)
        {
            return ((char*)array) + kIl2CppSizeOfArray + size * idx;
        }
#define load_array_elema(arr, idx, size) ((((uint8_t*)(arr)) + kIl2CppSizeOfArray) + ((size) * (idx)))

#define il2cpp_array_setwithsize(array, elementSize, index, value)  \
            do {    \
                void*__p = (void*) il2cpp_utils::array_utils::il2cpp_array_addr_with_size ((array), elementSize, (index)); \
                memcpy(__p, &(value), elementSize); \
            } while (0)
#define il2cpp_array_setrefwithsize(array, elementSize, index, value)  \
            do {    \
                void*__p = (void*) il2cpp_utils::array_utils::il2cpp_array_addr_with_size ((array), elementSize, (index)); \
                memcpy(__p, value, elementSize); \
                } while (0)
#define il2cpp_array_addr(array, type, index) ((type*)(void*) il2cpp_utils::array_utils::il2cpp_array_addr_with_size (array, sizeof (type), index))
#define il2cpp_array_get(array, type, index) ( *(type*)il2cpp_array_addr ((array), type, (index)) )
#define il2cpp_array_set(array, type, index, value)    \
            do {    \
                type *__p = (type *) il2cpp_array_addr ((array), type, (index));    \
                *__p = (value); \
            } while (0)
#define il2cpp_array_setref(array, index, value)  \
            do {    \
                void* *__p = (void* *) il2cpp_array_addr ((array), void*, (index)); \
                /* il2cpp_gc_wbarrier_set_arrayref ((array), __p, (MonoObject*)(value));    */\
                *__p = (value);    \
            } while (0)
    }





    // Init all of the usable il2cpp API, if it has yet to be initialized
    // Maximum length of characters of an exception message - 1
#define EXCEPTION_MESSAGE_SIZE 4096
// Returns a legible string from an Il2CppException*
    std::string ExceptionToString(Il2CppException* exp);

    // Returns the first matching class from the given namespace and typeName by searching through all assemblies that are loaded.
    Il2CppClass* GetClassFromName(const char* name_space, const char* type_name);

    // Framework provided by DaNike
    namespace il2cpp_type_check {
        template<typename T>
        struct il2cpp_arg_type_ {};

        template<typename T>
        using il2cpp_arg_type = il2cpp_arg_type_<std::decay_t<T>>;

        template<typename T>
        struct il2cpp_arg_type_<T*> { // we assume that pointers are already objects to get the type of
            static inline Il2CppType const* get(T const* arg) {
                return il2cpp_functions::class_get_type(
                    il2cpp_functions::object_get_class(reinterpret_cast<Il2CppObject*>(arg)));
            }
        };

        template<>
        struct il2cpp_arg_type_<int8_t> {
            static inline Il2CppType const* get(int8_t) {
                // return System.SByte
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "SByte"));
            }
        };

        template<>
        struct il2cpp_arg_type_<uint8_t> {
            static inline Il2CppType const* get(uint8_t) {
                // return System.Byte
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "SByte"));
            }
        };

        template<>
        struct il2cpp_arg_type_<float> {
            static inline Il2CppType const* get(float) {
                // return System.Single
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "Single"));
            }
        };

        template<>
        struct il2cpp_arg_type_<double> {
            static inline Il2CppType const* get(double) {
                // return System.Double
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "Double"));
            }
        };

        template<>
        struct il2cpp_arg_type_<int16_t> {
            static inline Il2CppType const* get(int16_t) {
                // return System.Int16
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "Int16"));
            }
        };

        template<>
        struct il2cpp_arg_type_<int> {
            static inline Il2CppType const* get(int) {
                // return System.Int32
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "Int32"));
            }
        };

        template<>
        struct il2cpp_arg_type_<int64_t> {
            static inline Il2CppType const* get(int64_t) {
                // return System.Int64
                return il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("System", "Int64"));
            }
        };

        // TODO Add more types

        template<typename T>
        struct il2cpp_arg_ptr {
            static inline void* get(T const& arg) {
                return reinterpret_cast<void*>(&arg);
            }
        };
        template<typename T>
        struct il2cpp_arg_ptr<T*> {
            static inline void* get(T* arg) {
                return reinterpret_cast<void*>(arg);
            }
        };
    }


    // Returns if a given MethodInfo's parameters match the Il2CppType array provided as type_arr
    bool ParameterMatch(const MethodInfo* method, Il2CppType** type_arr, int count);


    // Returns if a given MethodInfo's parameters match the Il2CppType array provided as type_arr
    bool ParameterMatch(const MethodInfo* method, const Il2CppType* const* type_arr, decltype(MethodInfo::parameters_count) count);

    template<typename... TArgs>
    // Returns if a given MethodInfo's parameters match the Il2CppTypes provided as args
    bool ParameterMatch(const MethodInfo* method, TArgs* ...args) {
        constexpr auto count = sizeof...(TArgs);
        Il2CppType* argarr[] = { reinterpret_cast<Il2CppType*>(args)... };
        return ParameterMatch(method, argarr, count);
    }

    // Returns if a given MethodInfo's parameters match the Il2CppTypes provided as a vector
    inline bool ParameterMatch(const MethodInfo* method, std::vector<const Il2CppType*> seq) {
        return ParameterMatch(method, seq.data(), seq.size());
    }

    //Array Sc2ad
    template<class T>
    struct Array : public Il2CppObject
    {
        static_assert(is_value_type<T>::value, "T must be a C# value type! (primitive, pointer or Struct)");
        /* bounds is NULL for szarrays */
        ArrayBounds* bounds;
        /* total number of elements of the array */
        int32_t max_length;
        T values[0];

        int32_t Length() {
            if (bounds) {
                return bounds->length;
            }
            return max_length;
        }
    };

    template<class T>
    Array<T>* CreateArray(const char* name_space, const char* type_name, size_t array_size)
    {
        Il2CppClass* klass = GetClassFromName(name_space, type_name);
        if (!klass)
        {
            LOG("il2cpp_utils: CreateArray: Couldn't get Il2CppClass from provide namespace and type name");
            return nullptr;
        }
        auto arr = il2cpp_functions::array_new(klass, array_size);
        return arr;
    }


    Il2CppArray* CreateIl2CppArray(const char* name_space, const char* type_name, size_t array_size);


    std::vector<const Il2CppType*> ClassVecToTypes(std::vector<const Il2CppClass*> seq);

    // Returns the MethodInfo for the method on the given class with the given name and types of arguments
// Created by zoller27osu
    const MethodInfo* FindMethod(Il2CppClass* klass, std::string_view methodName, std::vector<const Il2CppType*> argTypes);
    const MethodInfo* FindMethod(Il2CppClass* klass, std::string_view methodName, std::vector<const Il2CppClass*> argClasses);
    const MethodInfo* FindMethod(Il2CppClass* klass, std::string_view methodName, std::vector<std::string_view> argSpaceClass);

    // Returns the MethodInfo for the method on the given instance
    template<class... TArgs>
    const MethodInfo* FindMethod(Il2CppObject* instance, TArgs&&... params) {
        auto klass = il2cpp_functions::object_get_class(instance);
        if (klass == nullptr)
        {
            return nullptr;
        }
        return FindMethod(klass, params...);
    }

    const MethodInfo* FindMethodFromArgsName(Il2CppClass* klass, std::string_view methodName, std::vector<std::string_view> argNames);

    // Returns the MethodInfo for the method on the given class with the given name and number of arguments
 // Created by zoller27osu
    const MethodInfo* FindMethodUnsafe(Il2CppClass* klass, std::string_view methodName, int argsCount);

    const MethodInfo* FindMethodUnsafe(Il2CppObject* instance, std::string_view methodName, int argsCount);
    const MethodInfo* FindMethodUnsafe(std::string_view nameSpace, std::string_view className, std::string_view methodName, int argsCount);

    //template<typename TObj = Il2CppObject, typename... TArgs>
    //// Creates a new object of the given class using the given constructor parameters and casts it to TObj*
    //// Will only run a .ctor whose parameter types match the given arguments.
    //TObj* New(Il2CppClass* klass, TArgs const& ...args) {

    //    constexpr auto count = sizeof...(TArgs);
    //    auto ctor = GetMethod("", "", count);
    //    // object_new call
    //    auto obj = il2cpp_functions::object_new(klass);
    //    // runtime_invoke constructor with right type(s) of arguments, return null if constructor errors
    //    if (!RunMethod(obj, ".ctor", args...)) return nullptr;
    //    return reinterpret_cast<TObj*>(obj);
    //}


        // Returns the MethodInfo for the method on the given class with the given name and number of arguments
    // Created by zoller27osu
    const MethodInfo* GetMethod(Il2CppClass* klass, std::string_view methodName, int argsCount);

    // Returns the MethodInfo for the method on class found via namespace and name with the given name and number of arguments
    const MethodInfo* GetMethod(std::string_view nameSpace, std::string_view className, std::string_view methodName, int argsCount);

    // Returns MethodInfo for the set method of the given propertyName.
    const MethodInfo* GetPropertySetMethod(Il2CppClass* klass, std::string_view propertyName);

    // Returns MethodInfo for the get method of the given propertyName.
    const MethodInfo* GetPropertyGetMethod(Il2CppClass* klass, std::string_view propertyName);

    // Returns PropertyInfo given the name, if it exists
    const PropertyInfo* GetProperty(Il2CppClass* klass, std::string_view propertyName);

    inline auto ExtractValues() {
        return std::vector<void*>();
    }

    template<class T>
    std::vector<void*> ExtractValues(T&& arg) {
        using Dt = std::decay_t<T>;
        std::vector<void*> valVec;
        void* val;
        if constexpr (std::is_same_v<Dt, Il2CppType*> || std::is_same_v<Dt, Il2CppClass*>) {
            val = nullptr;
        }
        else if constexpr (std::is_pointer_v<Dt>) {
            val = reinterpret_cast<void*>(arg);
        }
        else {
            val = const_cast<Dt*>(&arg);
        }
        valVec.push_back(val);
        return valVec;
    }

    template<class T, class... TArgs>
    std::vector<void*> ExtractValues(T&& arg, TArgs&& ...args) {
        auto base = ExtractValues(arg);
        auto rec = ExtractValues(args...);
        base.insert(base.end(), rec.begin(), rec.end());
        return base;
    }

    template<typename TObj = Il2CppObject, typename... TArgs>
    // Creates a New object of the given class and parameters and casts it to TObj*
    // DOES NOT PERFORM TYPE-SAFE CHECKING!
    TObj* NewUnsafe(Il2CppClass* klass, TArgs&& ...args) {

        void* invokeParams[] = { reinterpret_cast<void*>(args)... };
        // object_new call
        auto obj = il2cpp_functions::object_new(klass);
        // runtime_invoke constructor with right number of args, return null if constructor errors
        constexpr auto count = sizeof...(TArgs);
        LOG("Attempting to find .ctor with paramCount: %lu for class name: %s", count, il2cpp_functions::class_get_name(klass));
        const MethodInfo* ctor = il2cpp_functions::class_get_method_from_name(klass, ".ctor", count);

        if (!ctor) {
            LOG("il2cpp_utils: New: Could not find constructor for provided class!");
            return nullptr;
        }
        Il2CppException* exp;
        il2cpp_functions::runtime_invoke(ctor, obj, invokeParams, &exp);
        if (exp) {
            LOG("il2cpp_utils: New: Failed with exception: %s", ExceptionToString(exp).c_str());
            return nullptr;
        }
        return reinterpret_cast<TObj*>(obj);
    }



    template<class TOut, class T, class... TArgs>
    // Runs a MethodInfo with the specified parameters and instance, with return type TOut
    // Assumes a static method if instance == nullptr
    // Returns false if it fails
    // Created by zoller27osu, modified by Sc2ad
    bool RunMethod(TOut* out, T* instance, const MethodInfo* method, TArgs&& ...params) {
        if (!method) {
            LOG("il2cpp_utils: RunMethod: Null MethodInfo!");
            return false;
        }

        // runtime_invoke will assume obj is unboxed and box it. We need to counter that for pre-boxed instances.
        // Note: we could also just call Runtime::Invoke directly, but box non-Il2CppObject instances ourselves as method->klass
        void* inst = instance;
        if constexpr (std::is_same_v<T, Il2CppObject>) {
            if (instance && method->klass->valuetype) {
                // We assume that if the method is for a ValueType and instance is an Il2CppObject, then it was pre-boxed.
                inst = il2cpp_functions::object_unbox(instance);
            }
        }


        Il2CppException* exp = nullptr;

        auto invokeParamsVec = ExtractValues(params...);
        auto ret = il2cpp_functions::runtime_invoke(method, instance, invokeParamsVec.data(), &exp);
        if constexpr (std::is_pointer<TOut>::value) {
            *out = reinterpret_cast<TOut>(ret);
        }
        else {
            *out = *reinterpret_cast<TOut*>(il2cpp_functions::object_unbox(ret));
        }

        if (exp) {
            LOG("il2cpp_utils: RunMethod: %s: Failed with exception: %s\n", il2cpp_functions::method_get_name(method),
                il2cpp_utils::ExceptionToString(exp).c_str());
            return false;
        }
        return true;
    }


    template<class T, class... TArgs>
    // Runs a MethodInfo with the specified parameters and instance; best for void return type
    // Assumes a static method if instance == nullptr
    // Returns false if it fails
    // Created by zoller27osu
    bool RunMethod(T* instance, const MethodInfo* method, TArgs&& ...params) {
        void* out = nullptr;
        return RunMethod(&out, instance, method, params...);
    }


    template<class TOut, class... TArgs>
    // Runs a static method with the specified method name, with return type TOut
    // Returns false if it fails
    // Created by zoller27osu, modified by Sc2ad
    bool RunMethod(TOut* out, Il2CppClass* klass, std::string_view methodName, TArgs&& ...params) {
        if (!klass) {
            LOG("il2cpp_utils: RunMethod: Null klass parameter!");
            return false;
        }
        const MethodInfo* method = GetMethod(klass, methodName, sizeof...(TArgs));
        if (!method) return false;
        Il2CppObject* instance = nullptr;
        return RunMethod(out, instance, method, params...);
    }


    template<class TOut, class... TArgs>
    // Runs a method with the specified method name, with return type TOut
    // Returns false if it fails
    // Created by zoller27osu, modified by Sc2ad
    bool RunMethod(TOut* out, Il2CppObject* instance, std::string_view methodName, TArgs&& ...params) {
        if (!instance) {
            LOG("il2cpp_utils: RunMethod: Null instance parameter!");
            return false;
        }
        auto klass = il2cpp_functions::object_get_class(instance);
        if (!klass) {
            LOG("il2cpp_utils: RunMethod: Could not get the object's class!");
            return false;
        }
        auto method = GetMethod(klass, methodName, sizeof...(TArgs));
        if (!method) return false;
        return RunMethod(out, instance, method, params...);
    }

    template<class... TArgs>
    // Runs a static method with the specified method name; best for void return type
    // Returns false if it fails
    // Created by zoller27osu
    bool RunMethod(Il2CppClass* klass, std::string_view methodName, TArgs&& ...params) {
        void* out = nullptr;
        return RunMethod(&out, klass, methodName, params...);
    }

    template<class... TArgs>
    // Runs a method with the specified method name; best for void return type
    // Returns false if it fails
    // Created by zoller27osu
    bool RunMethod(Il2CppObject* instance, std::string_view methodName, TArgs&& ...params) {
        void* out = nullptr;
        return RunMethod(&out, instance, methodName, params...);
    }

    template<typename TObj = Il2CppObject, typename... TArgs>
    // Creates a new object of the given class using the given constructor parameters and casts it to TObj*
    // Will only run a .ctor whose parameter types match the given arguments.
    TObj* New(Il2CppClass* klass, TArgs const& ...args) {

        // object_new call
        auto obj = il2cpp_functions::object_new(klass);
        // runtime_invoke constructor with right type(s) of arguments, return null if constructor errors
        if (!RunMethod(obj, ".ctor", args...)) return nullptr;
        return reinterpret_cast<TObj*>(obj);
    }

    // Returns the FieldInfo for the field of the given class with the given name
    // Created by zoller27osu
    FieldInfo* FindField(Il2CppClass* klass, std::string_view fieldName);


    template<typename TOut = Il2CppObject*>
    // Gets a value from the given object instance, and FieldInfo, with return type TOut
    // Returns false if it fails
    // Assumes a static field if instance == nullptr
    // Created by darknight1050, modified by Sc2ad and zoller27osu
    bool GetFieldValue(TOut* out, Il2CppObject* instance, FieldInfo* field) {
        if (!field) {
            LOG("il2cpp_utils: GetFieldValue: Null FieldInfo!");
            return false;
        }
        if (instance) {
            il2cpp_functions::field_get_value(instance, field, (void*)out);
        }
        else { // Fallback to perform a static field set
            il2cpp_functions::field_static_get_value(field, (void*)out);
        }
        return true;
    }

    template<typename TOut = Il2CppObject*>
    // Gets the value of the field with type TOut and the given name from the given class 
    // Returns false if it fails
    // Adapted by zoller27osu
    bool GetFieldValue(TOut* out, Il2CppClass* klass, std::string_view fieldName) {
        if (!klass) {
            LOG("il2cpp_utils: GetFieldValue: Could not find object class!");
            return false;
        }
        auto field = FindField(klass, fieldName);
        if (!field) return false;
        return GetFieldValue(out, nullptr, field);
    }

    template<typename TOut = Il2CppObject*>
    // Gets a value from the given object instance and field name, with return type TOut
    // Returns false if it fails
    // Created by darknight1050, modified by Sc2ad and zoller27osu
    bool GetFieldValue(TOut* out, Il2CppObject* instance, std::string_view fieldName) {
        if (!instance) {
            LOG("il2cpp_utils: GetFieldValue: Null instance parameter!");
            return false;
        }
        auto klass = il2cpp_functions::object_get_class(instance);
        if (!klass) {
            LOG("il2cpp_utils: GetFieldValue: Could not find object class!");
            return false;
        }
        auto field = FindField(klass, fieldName);
        if (!field) return false;
        return GetFieldValue(out, instance, field);
    }

    // Gets the value of a field with type TOut, given an object instance and the FieldInfo
    // Returns false if it fails
    // Assumes a static field if instance == nullptr
    // Created by zoller27osu
    template<class TOut = Il2CppObject*>
    TOut GetFieldValue(Il2CppObject* instance, FieldInfo* field) {
        static_assert(std::is_pointer<TOut>::value, "Please use the GetFieldValue that returns bool for non-pointer fields!");
        TOut out;
        GetFieldValue(&out, instance, field);
        return out;
    }

    // Gets the value of a given static field, given the field's class and name
    // Created by zoller27osu
    template<class TOut>
    TOut GetFieldValue(Il2CppClass* klass, std::string_view fieldName) {
        static_assert(std::is_pointer<TOut>::value, "Please use the GetFieldValue that returns bool for non-pointer fields!");
        TOut out;
        GetFieldValue(&out, klass, fieldName);
        return out;
    }

    // Gets the value of a given field, given an object instance and the field's name
    // Created by zoller27osu
    template<class TOut = Il2CppObject*>
    TOut GetFieldValue(Il2CppObject* instance, std::string_view fieldName) {
        static_assert(std::is_pointer<TOut>::value, "Please use the GetFieldValue that returns bool for non-pointer fields!");
        TOut out;
        GetFieldValue(&out, instance, fieldName);
        return out;
    }

    // Sets the value of a given field, given an object instance and FieldInfo
    // Returns false if it fails
    // Assumes static field if instance == nullptr
    bool SetFieldValue(Il2CppObject* instance, FieldInfo* field, void* value);

    // Sets the value of a given field, given an object instance and field name
    // Returns false if it fails
    // Adapted by zoller27osu
    bool SetFieldValue(Il2CppClass* klass, std::string_view fieldName, void* value);

    // Sets the value of a given field, given an object instance and field name
    // Returns false if it fails
    bool SetFieldValue(Il2CppObject* instance, std::string_view fieldName, void* value);

    template<typename T = MulticastDelegate, typename R, typename... TArgs>
    // Creates an Action and casts it to a MulticastDelegate*
    // Created by zoller27osu
    //typedef void ()
    //T* MakeAction(Il2CppObject* obj, <R, TArgs...> callback, const Il2CppType* actionType) {
    //    Il2CppClass* actionClass = il2cpp_functions::class_from_il2cpp_type(actionType);

    //    /*
    //    * TODO: call PlatformInvoke::MarshalFunctionPointerToDelegate directly instead of copying code from it,
    //    * or at least use a cache like utils::NativeDelegateMethodCache::GetNativeDelegate(nativeFunctionPointer);
    //    */
    //    const MethodInfo* invoke = il2cpp_functions::class_get_method_from_name(actionClass, "Invoke", -1);  // well-formed Actions have only 1 invoke method
    //    MethodInfo* method = (MethodInfo*)calloc(1, sizeof(MethodInfo));
    //    method->methodPointer = (Il2CppMethodPointer)callback;
    //    method->invoker_method = NULL;
    //    method->parameters_count = invoke->parameters_count;
    //    method->slot = kInvalidIl2CppMethodSlot;
    //    method->is_marshaled_from_native = true;  // "a fake MethodInfo wrapping a native function pointer"
    //    // In the event that a function is static, this will behave as normal
    //    if (obj == nullptr) method->flags |= METHOD_ATTRIBUTE_STATIC;

    //    // TODO: figure out why passing method directly doesn't work
    //    auto action = il2cpp_utils::NewUnsafe<T>(actionClass, obj, &method);
    //    auto asDelegate = reinterpret_cast<Delegate*>(action);
    //    if (asDelegate->method_ptr != (void*)callback) {
    //        LOG("Created Action's method_ptr (%p) is incorrect (should be %p)!", asDelegate->method_ptr, callback);
    //        return nullptr;
    //    }
    //    return action;
    //}

    //template<typename T = MulticastDelegate>
    //T* MakeAction(Il2CppObject* obj, void* callback, const Il2CppType* actionType) {
    //    auto tmp = reinterpret_cast<function_ptr_t<void>>(callback);
    //    return MakeAction(obj, tmp, actionType);
    //}

    // Calls the System.RuntimeType.MakeGenericType(System.Type gt, System.Type[] types) function
    Il2CppReflectionType* MakeGenericType(Il2CppReflectionType* gt, Il2CppArray* types);

    // Function made by zoller27osu, modified by Sc2ad
    Il2CppClass* MakeGeneric(const Il2CppClass* klass, std::initializer_list<const Il2CppClass*> args);

    // Gets a C# name of a type
    const char* TypeGetSimpleName(const Il2CppType* type);

    // Function made by zoller27osu, modified by Sc2ad
    // Logs information about the given MethodInfo* as log(DEBUG)
    void LogMethod(const MethodInfo* method);

    // Created by zoller27osu
    // Logs information about the given FieldInfo* as log(DEBUG)
    void LogField(FieldInfo* field);

    // Some parts provided by zoller27osu
    // Logs information about the given Il2CppClass* as log(DEBUG)
    void LogClass(const Il2CppClass* klass, bool logParents = true);

    // Creates a cs string (allocates it) with the given string_view and returns it
    Il2CppString* createcsstr(std::string_view inp);

    // Returns if a given source object is an object of the given class
    // Created by zoller27osu
    [[nodiscard]] bool Match(const Il2CppObject* source, const Il2CppClass* klass) noexcept;

    // Asserts that a given source object is an object of the given class
    // Created by zoller27osu
    bool AssertMatch(const Il2CppObject* source, const Il2CppClass* klass);

    template<class To, class From>
    // Downcasts a class from From* to To*
    [[nodiscard]] auto down_cast(From* in) noexcept {
        static_assert(std::is_convertible<To*, From*>::value);
        return static_cast<To*>(in);
    }

    template<typename... TArgs>
    // Runtime Invoke, but with a list initializer for args
    Il2CppObject* RuntimeInvoke(const MethodInfo* method, Il2CppObject* reference, Il2CppException** exc, TArgs&& ...args) {

        void** invokeParams = { reinterpret_cast<void*>(args)... };
        return il2cpp_functions::runtime_invoke(method, reference, invokeParams, exc);
    }
};


#endif // !IL2CPP_UTILS_HPP