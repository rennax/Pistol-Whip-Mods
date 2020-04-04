#pragma once
#include <il2cpp-object-internals.h>
#include <il2cpp-class-internals.h>
#include <il2cpp-api-types.h>
#include <il2cpp-tabledefs.h>
#include <windows.h>
#include "logger.h"
#include <type_traits>

// TAKEN FROM https://github.com/sc2ad/pistol-whip-hook/blob/fd7edc3d1d39d231e43c1430dbf4336045a056cc/shared/utils/il2cpp-functions.hpp
// A class which contains all available il2cpp functions
// Created by zoller27osu
class il2cpp_functions {
public:
	// note: the "inline" just make these definitions as well as declarations, so they don't have to be defined in the .cpp
	inline static void (*init)(const char* domain_name);
	inline static void (*init_utf16)(const Il2CppChar* domain_name);
	inline static void (*shutdown)();
	inline static void (*set_config_dir)(const char* config_path);
	inline static void (*set_data_dir)(const char* data_path);
	inline static void (*set_temp_dir)(const char* temp_path);
	inline static void (*set_commandline_arguments)(int argc, const char* const argv[], const char* basedir);
	inline static void (*set_commandline_arguments_utf16)(int argc, const Il2CppChar* const argv[], const char* basedir);
	inline static void (*set_config_utf16)(const Il2CppChar* executablePath);
	inline static void (*set_config)(const char* executablePath);

	inline static void (*set_memory_callbacks)(Il2CppMemoryCallbacks* callbacks);
	inline static const Il2CppImage* (*get_corlib)();
	inline static void (*add_internal_call)(const char* name, Il2CppMethodPointer method);
	inline static Il2CppMethodPointer(*resolve_icall)(const char* name);

	inline static void* (*alloc)(size_t size);
	inline static void (*free)(void* ptr);

	// array
	inline static Il2CppClass* (*array_class_get)(Il2CppClass* element_class, uint32_t rank);
	inline static uint32_t(*array_length)(Il2CppArray* array);
	inline static uint32_t(*array_get_byte_length)(Il2CppArray* array);
	inline static Il2CppArray* (*array_new)(Il2CppClass* elementTypeInfo, il2cpp_array_size_t length);
	inline static Il2CppArray* (*array_new_specific)(Il2CppClass* arrayTypeInfo, il2cpp_array_size_t length);
	inline static Il2CppArray* (*array_new_full)(Il2CppClass* array_class, il2cpp_array_size_t* lengths, il2cpp_array_size_t* lower_bounds);
	inline static Il2CppClass* (*bounded_array_class_get)(Il2CppClass* element_class, uint32_t rank, bool bounded);
	
	// assembly
	inline static int (*array_element_size)(const Il2CppClass* array_class);
	inline static const Il2CppImage* (*assembly_get_image)(const Il2CppAssembly* assembly);
	
	// class
	inline static const Il2CppType* (*class_enum_basetype)(Il2CppClass* klass);
	inline static bool (*class_is_generic)(const Il2CppClass* klass);
	inline static bool (*class_is_inflated)(const Il2CppClass* klass);
	inline static bool (*class_is_assignable_from)(Il2CppClass* klass, Il2CppClass* oklass);
	inline static bool (*class_is_subclass_of)(Il2CppClass* klass, Il2CppClass* klassc, bool check_interfaces);
	inline static bool (*class_has_parent)(Il2CppClass* klass, Il2CppClass* klassc);
	inline static Il2CppClass* (*class_from_il2cpp_type)(const Il2CppType* type);
	inline static Il2CppClass* (*class_from_name)(const Il2CppImage* image, const char* namespaze, const char* name);
	inline static Il2CppClass* (*class_from_system_type)(Il2CppReflectionType* type);
	inline static Il2CppClass* (*class_get_element_class)(Il2CppClass* klass);
	inline static const EventInfo* (*class_get_events)(Il2CppClass* klass, void** iter);
	inline static FieldInfo* (*class_get_fields)(Il2CppClass* klass, void** iter);
	inline static Il2CppClass* (*class_get_nested_types)(Il2CppClass* klass, void** iter);
	inline static Il2CppClass* (*class_get_interfaces)(Il2CppClass* klass, void** iter);
	inline static const PropertyInfo* (*class_get_properties)(Il2CppClass* klass, void** iter);
	inline static const PropertyInfo* (*class_get_property_from_name)(Il2CppClass* klass, const char* name);
	inline static FieldInfo* (*class_get_field_from_name)(Il2CppClass* klass, const char* name);
	inline static const MethodInfo* (*class_get_methods)(Il2CppClass* klass, void** iter);
	inline static const MethodInfo* (*class_get_method_from_name)(Il2CppClass* klass, const char* name, int argsCount);
	inline static const char* (*class_get_name)(Il2CppClass* klass);
	inline static const char* (*class_get_namespace)(Il2CppClass* klass);
	inline static Il2CppClass* (*class_get_parent)(Il2CppClass* klass);
	inline static Il2CppClass* (*class_get_declaring_type)(Il2CppClass* klass);
	inline static int32_t(*class_instance_size)(Il2CppClass* klass);
	inline static size_t(*class_num_fields)(const Il2CppClass* enumKlass);
	inline static bool (*class_is_valuetype)(const Il2CppClass* klass);
	inline static int32_t(*class_value_size)(Il2CppClass* klass, uint32_t* align);
	inline static bool (*class_is_blittable)(const Il2CppClass* klass);
	inline static int (*class_get_flags)(const Il2CppClass* klass);
	inline static bool (*class_is_abstract)(const Il2CppClass* klass);
	inline static bool (*class_is_interface)(const Il2CppClass* klass);
	inline static int (*class_array_element_size)(const Il2CppClass* klass);
	inline static Il2CppClass* (*class_from_type)(const Il2CppType* type);
	inline static const Il2CppType* (*class_get_type)(Il2CppClass* klass);
	inline static uint32_t(*class_get_type_token)(Il2CppClass* klass);
	inline static bool (*class_has_attribute)(Il2CppClass* klass, Il2CppClass* attr_class);
	inline static bool (*class_has_references)(Il2CppClass* klass);
	inline static bool (*class_is_enum)(const Il2CppClass* klass);
	inline static const Il2CppImage* (*class_get_image)(Il2CppClass* klass);
	inline static const char* (*class_get_assemblyname)(const Il2CppClass* klass);
	inline static int (*class_get_rank)(const Il2CppClass* klass);
	
	// testing only
	inline static size_t(*class_get_bitmap_size)(const Il2CppClass* klass);
	inline static void (*class_get_bitmap)(Il2CppClass* klass, size_t* bitmap);
	
	// stats
	inline static bool (*stats_dump_to_file)(const char* path);
	inline static uint64_t(*stats_get_value)(Il2CppStat stat);
	
	// domain
	inline static Il2CppDomain* (*domain_get)();
	inline static const Il2CppAssembly* (*domain_assembly_open)(Il2CppDomain* domain, const char* name);
	inline static const Il2CppAssembly** (*domain_get_assemblies)(const Il2CppDomain* domain, size_t* size);
	
	// exception
	inline static Il2CppException* (*exception_from_name_msg)(const Il2CppImage* image, const char* name_space, const char* name, const char* msg);
	inline static Il2CppException* (*get_exception_argument_null)(const char* arg);
	inline static void (*format_exception)(const Il2CppException* ex, char* message, int message_size);
	inline static void (*format_stack_trace)(const Il2CppException* ex, char* output, int output_size);
	inline static void (*unhandled_exception)(Il2CppException*);
	
	// field
	inline static int (*field_get_flags)(FieldInfo* field);
	inline static const char* (*field_get_name)(FieldInfo* field);
	inline static Il2CppClass* (*field_get_parent)(FieldInfo* field);
	inline static size_t(*field_get_offset)(FieldInfo* field);
	inline static const Il2CppType* (*field_get_type)(FieldInfo* field);
	inline static void (*field_get_value)(Il2CppObject* obj, FieldInfo* field, void* value);
	inline static Il2CppObject* (*field_get_value_object)(FieldInfo* field, Il2CppObject* obj);
	inline static bool (*field_has_attribute)(FieldInfo* field, Il2CppClass* attr_class);
	inline static void (*field_set_value)(Il2CppObject* obj, FieldInfo* field, void* value);
	inline static void (*field_static_get_value)(FieldInfo* field, void* value);
	inline static void (*field_static_set_value)(FieldInfo* field, void* value);
	inline static void (*field_set_value_object)(Il2CppObject* instance, FieldInfo* field, Il2CppObject* value);
	
	// gc
	inline static void (*gc_collect)(int maxGenerations);
	inline static int32_t(*gc_collect_a_little)();
	inline static void (*gc_disable)();
	inline static void (*gc_enable)();
	inline static bool (*gc_is_disabled)();
	inline static int64_t(*gc_get_used_size)();
	inline static int64_t(*gc_get_heap_size)();
	inline static void (*gc_wbarrier_set_field)(Il2CppObject* obj, void** targetAddress, void* object);
	
	// gchandle
	inline static uint32_t(*gchandle_new)(Il2CppObject* obj, bool pinned);
	inline static uint32_t(*gchandle_new_weakref)(Il2CppObject* obj, bool track_resurrection);
	inline static Il2CppObject* (*gchandle_get_target)(uint32_t gchandle);
	inline static void (*gchandle_free)(uint32_t gchandle);
	
	// liveness
	inline static void* (*unity_liveness_calculation_begin)(Il2CppClass* filter, int max_object_count, il2cpp_register_object_callback callback, void* userdata, il2cpp_WorldChangedCallback onWorldStarted, il2cpp_WorldChangedCallback onWorldStopped);
	inline static void (*unity_liveness_calculation_end)(void* state);
	inline static void (*unity_liveness_calculation_from_root)(Il2CppObject* root, void* state);
	inline static void (*unity_liveness_calculation_from_statics)(void* state);
	
	// method
	inline static const Il2CppType* (*method_get_return_type)(const MethodInfo* method);
	inline static Il2CppClass* (*method_get_declaring_type)(const MethodInfo* method);
	inline static const char* (*method_get_name)(const MethodInfo* method);
	inline static const MethodInfo* (*method_get_from_reflection)(const Il2CppReflectionMethod* method);
	inline static Il2CppReflectionMethod* (*method_get_object)(const MethodInfo* method, Il2CppClass* refclass);
	inline static bool (*method_is_generic)(const MethodInfo* method);
	inline static bool (*method_is_inflated)(const MethodInfo* method);
	inline static bool (*method_is_instance)(const MethodInfo* method);
	inline static uint32_t(*method_get_param_count)(const MethodInfo* method);
	inline static const Il2CppType* (*method_get_param)(const MethodInfo* method, uint32_t index);
	inline static Il2CppClass* (*method_get_class)(const MethodInfo* method);
	inline static bool (*method_has_attribute)(const MethodInfo* method, Il2CppClass* attr_class);
	inline static uint32_t(*method_get_flags)(const MethodInfo* method, uint32_t* iflags);
	inline static uint32_t(*method_get_token)(const MethodInfo* method);
	inline static const char* (*method_get_param_name)(const MethodInfo* method, uint32_t index);
	inline static void (*profiler_install)(Il2CppProfiler* prof, Il2CppProfileFunc shutdown_callback);
	inline static void (*profiler_set_events)(Il2CppProfileFlags events);
	inline static void (*profiler_install_enter_leave)(Il2CppProfileMethodFunc enter, Il2CppProfileMethodFunc fleave);
	inline static void (*profiler_install_allocation)(Il2CppProfileAllocFunc callback);
	inline static void (*profiler_install_gc)(Il2CppProfileGCFunc callback, Il2CppProfileGCResizeFunc heap_resize_callback);
	inline static void (*profiler_install_fileio)(Il2CppProfileFileIOFunc callback);
	inline static void (*profiler_install_thread)(Il2CppProfileThreadFunc start, Il2CppProfileThreadFunc end);
	
	// Property
	inline static uint32_t(*property_get_flags)(const PropertyInfo* prop);
	inline static const MethodInfo* (*property_get_get_method)(const PropertyInfo* prop);
	inline static const MethodInfo* (*property_get_set_method)(const PropertyInfo* prop);
	inline static const char* (*property_get_name)(const PropertyInfo* prop);
	inline static Il2CppClass* (*property_get_parent)(const PropertyInfo* prop);

	// object
	inline static Il2CppClass* (*object_get_class)(Il2CppObject* obj);
	inline static uint32_t(*object_get_size)(Il2CppObject* obj);
	inline static const MethodInfo* (*object_get_virtual_method)(Il2CppObject* obj, const MethodInfo* method);
	inline static Il2CppObject* (*object_new)(const Il2CppClass* klass);
	inline static void* (*object_unbox)(Il2CppObject* obj);
	inline static Il2CppObject* (*value_box)(Il2CppClass* klass, void* data);

	// monitor
	inline static void (*monitor_enter)(Il2CppObject* obj);
	inline static bool (*monitor_try_enter)(Il2CppObject* obj, uint32_t timeout);
	inline static void (*monitor_exit)(Il2CppObject* obj);
	inline static void (*monitor_pulse)(Il2CppObject* obj);
	inline static void (*monitor_pulse_all)(Il2CppObject* obj);
	inline static void (*monitor_wait)(Il2CppObject* obj);
	inline static bool (*monitor_try_wait)(Il2CppObject* obj, uint32_t timeout);

	// runtime
	inline static Il2CppObject* (*runtime_invoke)(const MethodInfo* method, void* obj, void** params, Il2CppException** exc);
	inline static Il2CppObject* (*runtime_invoke_convert_args)(const MethodInfo* method, void* obj, Il2CppObject** params, int paramCount, Il2CppException** exc);
	inline static void (*runtime_class_init)(Il2CppClass* klass);
	inline static void (*runtime_object_init)(Il2CppObject* obj);
	inline static void (*runtime_object_init_exception)(Il2CppObject* obj, Il2CppException** exc);
	inline static void (*runtime_unhandled_exception_policy_set)(Il2CppRuntimeUnhandledExceptionPolicy value);
	
	// string
	inline static int32_t(*string_length)(Il2CppString* str);
	inline static Il2CppChar* (*string_chars)(Il2CppString* str);
	inline static Il2CppString* (*string_new)(const char* str);
	inline static Il2CppString* (*string_new_len)(const char* str, uint32_t length);
	inline static Il2CppString* (*string_new_utf16)(const Il2CppChar* text, int32_t len);
	inline static Il2CppString* (*string_new_wrapper)(const char* str);
	inline static Il2CppString* (*string_intern)(Il2CppString* str);
	inline static Il2CppString* (*string_is_interned)(Il2CppString* str);
	
	// thread
	inline static Il2CppThread* (*thread_current)();
	inline static Il2CppThread* (*thread_attach)(Il2CppDomain* domain);
	inline static void (*thread_detach)(Il2CppThread* thread);
	inline static Il2CppThread** (*thread_get_all_attached_threads)(size_t* size);
	inline static bool (*is_vm_thread)(Il2CppThread* thread);
	
	// stacktrace
	inline static void (*current_thread_walk_frame_stack)(Il2CppFrameWalkFunc func, void* user_data);
	inline static void (*thread_walk_frame_stack)(Il2CppThread* thread, Il2CppFrameWalkFunc func, void* user_data);
	inline static bool (*current_thread_get_top_frame)(Il2CppStackFrameInfo* frame);
	inline static bool (*thread_get_top_frame)(Il2CppThread* thread, Il2CppStackFrameInfo* frame);
	inline static bool (*current_thread_get_frame_at)(int32_t offset, Il2CppStackFrameInfo* frame);
	inline static bool (*thread_get_frame_at)(Il2CppThread* thread, int32_t offset, Il2CppStackFrameInfo* frame);
	inline static int32_t(*current_thread_get_stack_depth)();
	inline static int32_t(*thread_get_stack_depth)(Il2CppThread* thread);
	
	// type
	inline static Il2CppObject* (*type_get_object)(const Il2CppType* type);
	inline static int (*type_get_type)(const Il2CppType* type);
	inline static Il2CppClass* (*type_get_class_or_element_class)(const Il2CppType* type);
	inline static char* (*type_get_name)(const Il2CppType* type);
	inline static bool (*type_is_byref)(const Il2CppType* type);
	inline static uint32_t(*type_get_attrs)(const Il2CppType* type);
	inline static bool (*type_equals)(const Il2CppType* type, const Il2CppType* otherType);
	inline static char* (*type_get_assembly_qualified_name)(const Il2CppType* type);
	
	// image
	inline static const Il2CppAssembly* (*image_get_assembly)(const Il2CppImage* image);
	inline static const char* (*image_get_name)(const Il2CppImage* image);
	inline static const char* (*image_get_filename)(const Il2CppImage* image);
	inline static const MethodInfo* (*image_get_entry_point)(const Il2CppImage* image);
	inline static size_t(*image_get_class_count)(const Il2CppImage* image);
	inline static const Il2CppClass* (*image_get_class)(const Il2CppImage* image, size_t index);
	
	// Memory information
	inline static Il2CppManagedMemorySnapshot* (*capture_memory_snapshot)();
	inline static void (*free_captured_memory_snapshot)(Il2CppManagedMemorySnapshot* snapshot);
	inline static void (*set_find_plugin_callback)(Il2CppSetFindPlugInCallback method);
	
	// Logging
	inline static void (*register_log_callback)(Il2CppLogCallback method);
	
	// Debugger
	inline static void (*debugger_set_agent_options)(const char* options);
	inline static bool (*is_debugger_attached)();
	
	// TLS module
	inline static void (*unity_install_unitytls_interface)(const void* unitytlsInterfaceStruct);
	
	// custom attributes
	inline static Il2CppCustomAttrInfo* (*custom_attrs_from_class)(Il2CppClass* klass);
	inline static Il2CppCustomAttrInfo* (*custom_attrs_from_method)(const MethodInfo* method);
	inline static Il2CppObject* (*custom_attrs_get_attr)(Il2CppCustomAttrInfo* ainfo, Il2CppClass* attr_klass);
	inline static bool (*custom_attrs_has_attr)(Il2CppCustomAttrInfo* ainfo, Il2CppClass* attr_klass);
	inline static Il2CppArray* (*custom_attrs_construct)(Il2CppCustomAttrInfo* cinfo);
	inline static void (*custom_attrs_free)(Il2CppCustomAttrInfo* ainfo);

	// MANUALLY DEFINED CONST DEFINITIONS
	inline static const Il2CppType* (*class_get_type_const)(const Il2CppClass* klass);
	inline static const char* (*class_get_name_const)(const Il2CppClass* klass);



	inline static const Il2CppMetadataRegistration** s_Il2CppMetadataRegistrationPtr;
	inline static const void** s_GlobalMetadataPtr;
	inline static const Il2CppGlobalMetadataHeader** s_GlobalMetadataHeaderPtr;

	inline static std::remove_pointer_t<decltype(il2cpp_functions::s_GlobalMetadataPtr)> s_GlobalMetadata = nullptr;
	inline static std::remove_pointer_t<decltype(il2cpp_functions::s_GlobalMetadataHeaderPtr)> s_GlobalMetadataHeader = nullptr;
	inline static const Il2CppDefaults* defaults;

	// must be done on-demand because the pointers aren't necessarily correct at the time of il2cpp_functions::Init
	inline static void CheckS_GlobalMetadata() {
		if (!s_GlobalMetadataHeader) {
			s_GlobalMetadata = *(il2cpp_functions::s_GlobalMetadataPtr);
			s_GlobalMetadataHeader = *(il2cpp_functions::s_GlobalMetadataHeaderPtr);
			LOG("DEBUG: sanity: %X (should be 0xFAB11BAF)", s_GlobalMetadataHeader->sanity);
			LOG("DEBUG: version: %i", s_GlobalMetadataHeader->version);
			assert(s_GlobalMetadataHeader->sanity == 0xFAB11BAF);
			LOG("DEBUG: typeDefinitionsOffset: %i", s_GlobalMetadataHeader->typeDefinitionsOffset);
			LOG("DEBUG: exportedTypeDefinitionsOffset: %i", s_GlobalMetadataHeader->exportedTypeDefinitionsOffset);
			LOG("DEBUG: nestedTypesOffset: %i", s_GlobalMetadataHeader->nestedTypesOffset);
			// TODO: use il2cpp_functions::defaults to define the il2cpp_defaults variable mentioned in il2cpp-class-internals.h
		}
	}

	// COPIES OF FREQUENTLY INLINED NON-API LIBIL2CPP FUNCTIONS:
	static const char* MetadataCache_GetStringFromIndex(StringIndex index);
	static const Il2CppTypeDefinition* MetadataCache_GetTypeDefinitionFromIndex(TypeDefinitionIndex index);
	static TypeDefinitionIndex MetadataCache_GetExportedTypeFromIndex(TypeDefinitionIndex index);
	static const Il2CppGenericContainer* MetadataCache_GetGenericContainerFromIndex(GenericContainerIndex index);
	static const Il2CppGenericParameter* MetadataCache_GetGenericParameterFromIndex(GenericParameterIndex index);
	static Il2CppClass* MetadataCache_GetNestedTypeFromIndex(NestedTypeIndex index);
	static const TypeDefinitionIndex MetadataCache_GetIndexForTypeDefinition(const Il2CppClass* typeDefinition);


	// Whether all of the il2cpp functions have been initialized or not
	inline static bool initialized = false;
	// Initializes all of the IL2CPP functions via dlopen and dlsym for use.
	static void Init(HMODULE module);
};

