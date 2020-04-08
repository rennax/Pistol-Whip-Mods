#include "pch.h"
#include "il2cpp_functions.hpp"
#include <windows.h>
#include <libloaderapi2.h>
#include <sstream>
#include <strsafe.h>

#define LOGIT
#ifndef LOGIT
#include "logger.h"
#else
static void LOG(const char*, ...) {};
#endif // !LOGIT


//// copies of the highly-inlinable functions
//const Il2CppTypeDefinition* il2cpp_functions::MetadataCache_GetTypeDefinitionFromIndex(TypeDefinitionIndex index) {
//    CheckS_GlobalMetadata();
//    if (index == kTypeDefinitionIndexInvalid) return NULL;
//
//    IL2CPP_ASSERT(index >= 0 && static_cast<uint32_t>(index) < s_GlobalMetadataHeader->typeDefinitionsCount / sizeof(Il2CppTypeDefinition));
//    auto typeDefinitions = (const Il2CppTypeDefinition*)((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->typeDefinitionsOffset);
//    return typeDefinitions + index;
//}
//
//const char* il2cpp_functions::MetadataCache_GetStringFromIndex(StringIndex index) {
//    CheckS_GlobalMetadata();
//    IL2CPP_ASSERT(index <= s_GlobalMetadataHeader->stringCount);
//    const char* strings = ((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->stringOffset) + index;
//    return strings;
//}
//
//const Il2CppGenericContainer* il2cpp_functions::MetadataCache_GetGenericContainerFromIndex(GenericContainerIndex index) {
//    CheckS_GlobalMetadata();
//    if (index == kGenericContainerIndexInvalid) return NULL;
//
//    IL2CPP_ASSERT(index >= 0 && static_cast<uint32_t>(index) <= s_GlobalMetadataHeader->genericContainersCount / sizeof(Il2CppGenericContainer));
//    const Il2CppGenericContainer* genericContainers = (const Il2CppGenericContainer*)((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->genericContainersOffset);
//    return genericContainers + index;
//}
//
//const Il2CppGenericParameter* il2cpp_functions::MetadataCache_GetGenericParameterFromIndex(GenericParameterIndex index) {
//    CheckS_GlobalMetadata();
//    if (index == kGenericParameterIndexInvalid) return NULL;
//
//    IL2CPP_ASSERT(index >= 0 && static_cast<uint32_t>(index) <= s_GlobalMetadataHeader->genericParametersCount / sizeof(Il2CppGenericParameter));
//    const Il2CppGenericParameter* genericParameters = (const Il2CppGenericParameter*)((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->genericParametersOffset);
//    return genericParameters + index;
//}
//
//TypeDefinitionIndex il2cpp_functions::MetadataCache_GetExportedTypeFromIndex(TypeDefinitionIndex index) {
//    CheckS_GlobalMetadata();
//    if (index == kTypeDefinitionIndexInvalid) return kTypeDefinitionIndexInvalid;
//
//    IL2CPP_ASSERT(index >= 0 && static_cast<uint32_t>(index) < s_GlobalMetadataHeader->exportedTypeDefinitionsCount / sizeof(TypeDefinitionIndex));
//    auto exportedTypes = (TypeDefinitionIndex*)((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->exportedTypeDefinitionsOffset);
//    return *(exportedTypes + index);
//}
//
//Il2CppClass* il2cpp_functions::MetadataCache_GetNestedTypeFromIndex(NestedTypeIndex index) {
//    CheckS_GlobalMetadata();
//    IL2CPP_ASSERT(index >= 0 && static_cast<uint32_t>(index) <= s_GlobalMetadataHeader->nestedTypesCount / sizeof(TypeDefinitionIndex));
//    auto nestedTypeIndices = (const TypeDefinitionIndex*)((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->nestedTypesOffset);
//
//    return il2cpp_functions::MetadataCache_GetTypeInfoFromTypeDefinitionIndex(nestedTypeIndices[index]);
//}
//
//const TypeDefinitionIndex il2cpp_functions::MetadataCache_GetIndexForTypeDefinition(const Il2CppClass* typeDefinition) {
//    CheckS_GlobalMetadata();
//    IL2CPP_ASSERT(typeDefinition->typeDefinition);
//    const Il2CppTypeDefinition* typeDefinitions = (const Il2CppTypeDefinition*)((const char*)s_GlobalMetadata + s_GlobalMetadataHeader->typeDefinitionsOffset);
//
//    IL2CPP_ASSERT(typeDefinition->typeDefinition >= typeDefinitions && typeDefinition->typeDefinition < typeDefinitions + s_GlobalMetadataHeader->typeDefinitionsCount);
//
//    ptrdiff_t index = typeDefinition->typeDefinition - typeDefinitions;
//    IL2CPP_ASSERT(index <= std::numeric_limits<TypeDefinitionIndex>::max());
//    return static_cast<TypeDefinitionIndex>(index);
//}
//
//const char* il2cpp_functions::Type_GetName(const Il2CppType* type, Il2CppTypeNameFormat format) {
//    if (!il2cpp_functions::_Type_GetName_) return nullptr;
//    const auto& strRef = il2cpp_functions::_Type_GetName_(type, format);  // TODO figure out why this ref step is needed for 2019
//    const auto str = strRef;
//    return str.c_str();
//}




void il2cpp_functions::Init(HMODULE module)
{
	if (!initialized)
	{
		initialized = true;

        *(void**)(&init) = GetProcAddress(module, "il2cpp_init");
        LOG("Loaded: il2cpp_init");
        *(void**)(&init_utf16) = GetProcAddress(module, "il2cpp_init_utf16");
        LOG("Loaded: il2cpp_init_utf16");
        *(void**)(&shutdown) = GetProcAddress(module, "il2cpp_shutdown");
        LOG("Loaded: il2cpp_shutdown");
        *(void**)(&set_config_dir) = GetProcAddress(module, "il2cpp_set_config_dir");
        LOG("Loaded: il2cpp_set_config_dir");
        *(void**)(&set_data_dir) = GetProcAddress(module, "il2cpp_set_data_dir");
        LOG("Loaded: il2cpp_set_data_dir");
        *(void**)(&set_temp_dir) = GetProcAddress(module, "il2cpp_set_temp_dir");
        LOG("Loaded: il2cpp_set_temp_dir");
        *(void**)(&set_commandline_arguments) = GetProcAddress(module, "il2cpp_set_commandline_arguments");
        LOG("Loaded: il2cpp_set_commandline_arguments");
        *(void**)(&set_commandline_arguments_utf16) = GetProcAddress(module, "il2cpp_set_commandline_arguments_utf16");
        LOG("Loaded: il2cpp_set_commandline_arguments_utf16");
        *(void**)(&set_config_utf16) = GetProcAddress(module, "il2cpp_set_config_utf16");
        LOG("Loaded: il2cpp_set_config_utf16");
        *(void**)(&set_config) = GetProcAddress(module, "il2cpp_set_config");
        LOG("Loaded: il2cpp_set_config");
        *(void**)(&set_memory_callbacks) = GetProcAddress(module, "il2cpp_set_memory_callbacks");
        LOG("Loaded: il2cpp_set_memory_callbacks");
        *(void**)(&get_corlib) = GetProcAddress(module, "il2cpp_get_corlib");
        LOG("Loaded: il2cpp_get_corlib");
        *(void**)(&add_internal_call) = GetProcAddress(module, "il2cpp_add_internal_call");
        LOG("Loaded: il2cpp_add_internal_call");
        *(void**)(&resolve_icall) = GetProcAddress(module, "il2cpp_resolve_icall");
        LOG("Loaded: il2cpp_resolve_icall");
        *(void**)(&alloc) = GetProcAddress(module, "il2cpp_alloc");
        LOG("Loaded: il2cpp_alloc");
        *(void**)(&free) = GetProcAddress(module, "il2cpp_free");
        LOG("Loaded: il2cpp_free");
        *(void**)(&array_class_get) = GetProcAddress(module, "il2cpp_array_class_get");
        LOG("Loaded: il2cpp_array_class_get");
        *(void**)(&array_length) = GetProcAddress(module, "il2cpp_array_length");
        LOG("Loaded: il2cpp_array_length");
        *(void**)(&array_get_byte_length) = GetProcAddress(module, "il2cpp_array_get_byte_length");
        LOG("Loaded: il2cpp_array_get_byte_length");
        *(void**)(&array_new) = GetProcAddress(module, "il2cpp_array_new");
        LOG("Loaded: il2cpp_array_new");
        *(void**)(&array_new_specific) = GetProcAddress(module, "il2cpp_array_new_specific");
        LOG("Loaded: il2cpp_array_new_specific");
        *(void**)(&array_new_full) = GetProcAddress(module, "il2cpp_array_new_full");
        LOG("Loaded: il2cpp_array_new_full");
        *(void**)(&bounded_array_class_get) = GetProcAddress(module, "il2cpp_bounded_array_class_get");
        LOG("Loaded: il2cpp_bounded_array_class_get");
        *(void**)(&array_element_size) = GetProcAddress(module, "il2cpp_array_element_size");
        LOG("Loaded: il2cpp_array_element_size");
        *(void**)(&assembly_get_image) = GetProcAddress(module, "il2cpp_assembly_get_image");
        LOG("Loaded: il2cpp_assembly_get_image");
        *(void**)(&class_enum_basetype) = GetProcAddress(module, "il2cpp_class_enum_basetype");
        LOG("Loaded: il2cpp_class_enum_basetype");
        *(void**)(&class_is_generic) = GetProcAddress(module, "il2cpp_class_is_generic");
        LOG("Loaded: il2cpp_class_is_generic");
        *(void**)(&class_is_inflated) = GetProcAddress(module, "il2cpp_class_is_inflated");
        LOG("Loaded: il2cpp_class_is_inflated");
        *(void**)(&class_is_assignable_from) = GetProcAddress(module, "il2cpp_class_is_assignable_from");
        LOG("Loaded: il2cpp_class_is_assignable_from");
        *(void**)(&class_is_subclass_of) = GetProcAddress(module, "il2cpp_class_is_subclass_of");
        LOG("Loaded: il2cpp_class_is_subclass_of");
        *(void**)(&class_has_parent) = GetProcAddress(module, "il2cpp_class_has_parent");
        LOG("Loaded: il2cpp_class_has_parent");
        *(void**)(&class_from_il2cpp_type) = GetProcAddress(module, "il2cpp_class_from_il2cpp_type");
        LOG("Loaded: il2cpp_class_from_il2cpp_type");
        *(void**)(&class_from_name) = GetProcAddress(module, "il2cpp_class_from_name");
        LOG("Loaded: il2cpp_class_from_name");
        *(void**)(&class_from_system_type) = GetProcAddress(module, "il2cpp_class_from_system_type");
        LOG("Loaded: il2cpp_class_from_system_type");
        *(void**)(&class_get_element_class) = GetProcAddress(module, "il2cpp_class_get_element_class");
        LOG("Loaded: il2cpp_class_get_element_class");
        *(void**)(&class_get_events) = GetProcAddress(module, "il2cpp_class_get_events");
        LOG("Loaded: il2cpp_class_get_events");
        *(void**)(&class_get_fields) = GetProcAddress(module, "il2cpp_class_get_fields");
        LOG("Loaded: il2cpp_class_get_fields");
        *(void**)(&class_get_nested_types) = GetProcAddress(module, "il2cpp_class_get_nested_types");
        LOG("Loaded: il2cpp_class_get_nested_types");
        *(void**)(&class_get_interfaces) = GetProcAddress(module, "il2cpp_class_get_interfaces");
        LOG("Loaded: il2cpp_class_get_interfaces");
        *(void**)(&class_get_properties) = GetProcAddress(module, "il2cpp_class_get_properties");
        LOG("Loaded: il2cpp_class_get_properties");
        *(void**)(&class_get_property_from_name) = GetProcAddress(module, "il2cpp_class_get_property_from_name");
        LOG("Loaded: il2cpp_class_get_property_from_name");
        *(void**)(&class_get_field_from_name) = GetProcAddress(module, "il2cpp_class_get_field_from_name");
        LOG("Loaded: il2cpp_class_get_field_from_name");
        *(void**)(&class_get_methods) = GetProcAddress(module, "il2cpp_class_get_methods");
        LOG("Loaded: il2cpp_class_get_methods");
        *(void**)(&class_get_method_from_name) = GetProcAddress(module, "il2cpp_class_get_method_from_name");
        LOG("Loaded: il2cpp_class_get_method_from_name");
        *(void**)(&class_get_name) = GetProcAddress(module, "il2cpp_class_get_name");
        LOG("Loaded: il2cpp_class_get_name");
        *(void**)(&class_get_namespace) = GetProcAddress(module, "il2cpp_class_get_namespace");
        LOG("Loaded: il2cpp_class_get_namespace");
        *(void**)(&class_get_parent) = GetProcAddress(module, "il2cpp_class_get_parent");
        LOG("Loaded: il2cpp_class_get_parent");
        *(void**)(&class_get_declaring_type) = GetProcAddress(module, "il2cpp_class_get_declaring_type");
        LOG("Loaded: il2cpp_class_get_declaring_type");
        *(void**)(&class_instance_size) = GetProcAddress(module, "il2cpp_class_instance_size");
        LOG("Loaded: il2cpp_class_instance_size");
        *(void**)(&class_num_fields) = GetProcAddress(module, "il2cpp_class_num_fields");
        LOG("Loaded: il2cpp_class_num_fields");
        *(void**)(&class_is_valuetype) = GetProcAddress(module, "il2cpp_class_is_valuetype");
        LOG("Loaded: il2cpp_class_is_valuetype");
        *(void**)(&class_value_size) = GetProcAddress(module, "il2cpp_class_value_size");
        LOG("Loaded: il2cpp_class_value_size");
        *(void**)(&class_is_blittable) = GetProcAddress(module, "il2cpp_class_is_blittable");
        LOG("Loaded: il2cpp_class_is_blittable");
        *(void**)(&class_get_flags) = GetProcAddress(module, "il2cpp_class_get_flags");
        LOG("Loaded: il2cpp_class_get_flags");
        *(void**)(&class_is_abstract) = GetProcAddress(module, "il2cpp_class_is_abstract");
        LOG("Loaded: il2cpp_class_is_abstract");
        *(void**)(&class_is_interface) = GetProcAddress(module, "il2cpp_class_is_interface");
        LOG("Loaded: il2cpp_class_is_interface");
        *(void**)(&class_array_element_size) = GetProcAddress(module, "il2cpp_class_array_element_size");
        LOG("Loaded: il2cpp_class_array_element_size");
        *(void**)(&class_from_type) = GetProcAddress(module, "il2cpp_class_from_type");
        LOG("Loaded: il2cpp_class_from_type");
        *(void**)(&class_get_type) = GetProcAddress(module, "il2cpp_class_get_type");
        LOG("Loaded: il2cpp_class_get_type");
        *(void**)(&class_get_type_token) = GetProcAddress(module, "il2cpp_class_get_type_token");
        LOG("Loaded: il2cpp_class_get_type_token");
        *(void**)(&class_has_attribute) = GetProcAddress(module, "il2cpp_class_has_attribute");
        LOG("Loaded: il2cpp_class_has_attribute");
        *(void**)(&class_has_references) = GetProcAddress(module, "il2cpp_class_has_references");
        LOG("Loaded: il2cpp_class_has_references");
        *(void**)(&class_is_enum) = GetProcAddress(module, "il2cpp_class_is_enum");
        LOG("Loaded: il2cpp_class_is_enum");
        *(void**)(&class_get_image) = GetProcAddress(module, "il2cpp_class_get_image");
        LOG("Loaded: il2cpp_class_get_image");
        *(void**)(&class_get_assemblyname) = GetProcAddress(module, "il2cpp_class_get_assemblyname");
        LOG("Loaded: il2cpp_class_get_assemblyname");
        *(void**)(&class_get_rank) = GetProcAddress(module, "il2cpp_class_get_rank");
        LOG("Loaded: il2cpp_class_get_rank");
        *(void**)(&class_get_bitmap_size) = GetProcAddress(module, "il2cpp_class_get_bitmap_size");
        LOG("Loaded: il2cpp_class_get_bitmap_size");
        *(void**)(&class_get_bitmap) = GetProcAddress(module, "il2cpp_class_get_bitmap");
        LOG("Loaded: il2cpp_class_get_bitmap");
        *(void**)(&stats_dump_to_file) = GetProcAddress(module, "il2cpp_stats_dump_to_file");
        LOG("Loaded: il2cpp_stats_dump_to_file");
        *(void**)(&stats_get_value) = GetProcAddress(module, "il2cpp_stats_get_value");
        LOG("Loaded: il2cpp_stats_get_value");
        *(void**)(&domain_get) = GetProcAddress(module, "il2cpp_domain_get");
        LOG("Loaded: il2cpp_domain_get");
        *(void**)(&domain_assembly_open) = GetProcAddress(module, "il2cpp_domain_assembly_open");
        LOG("Loaded: il2cpp_domain_assembly_open");
        *(void**)(&domain_get_assemblies) = GetProcAddress(module, "il2cpp_domain_get_assemblies");
        LOG("Loaded: il2cpp_domain_get_assemblies");
        *(void**)(&exception_from_name_msg) = GetProcAddress(module, "il2cpp_exception_from_name_msg");
        LOG("Loaded: il2cpp_exception_from_name_msg");
        *(void**)(&get_exception_argument_null) = GetProcAddress(module, "il2cpp_get_exception_argument_null");
        LOG("Loaded: il2cpp_get_exception_argument_null");
        *(void**)(&format_exception) = GetProcAddress(module, "il2cpp_format_exception");
        LOG("Loaded: il2cpp_format_exception");
        *(void**)(&format_stack_trace) = GetProcAddress(module, "il2cpp_format_stack_trace");
        LOG("Loaded: il2cpp_format_stack_trace");
        *(void**)(&unhandled_exception) = GetProcAddress(module, "il2cpp_unhandled_exception");
        LOG("Loaded: il2cpp_unhandled_exception");
        *(void**)(&field_get_flags) = GetProcAddress(module, "il2cpp_field_get_flags");
        LOG("Loaded: il2cpp_field_get_flags");
        *(void**)(&field_get_name) = GetProcAddress(module, "il2cpp_field_get_name");
        LOG("Loaded: il2cpp_field_get_name");
        *(void**)(&field_get_parent) = GetProcAddress(module, "il2cpp_field_get_parent");
        LOG("Loaded: il2cpp_field_get_parent");
        *(void**)(&field_get_offset) = GetProcAddress(module, "il2cpp_field_get_offset");
        LOG("Loaded: il2cpp_field_get_offset");
        *(void**)(&field_get_type) = GetProcAddress(module, "il2cpp_field_get_type");
        LOG("Loaded: il2cpp_field_get_type");
        *(void**)(&field_get_value) = GetProcAddress(module, "il2cpp_field_get_value");
        LOG("Loaded: il2cpp_field_get_value");
        *(void**)(&field_get_value_object) = GetProcAddress(module, "il2cpp_field_get_value_object");
        LOG("Loaded: il2cpp_field_get_value_object");
        *(void**)(&field_has_attribute) = GetProcAddress(module, "il2cpp_field_has_attribute");
        LOG("Loaded: il2cpp_field_has_attribute");
        *(void**)(&field_set_value) = GetProcAddress(module, "il2cpp_field_set_value");
        LOG("Loaded: il2cpp_field_set_value");
        *(void**)(&field_static_get_value) = GetProcAddress(module, "il2cpp_field_static_get_value");
        LOG("Loaded: il2cpp_field_static_get_value");
        *(void**)(&field_static_set_value) = GetProcAddress(module, "il2cpp_field_static_set_value");
        LOG("Loaded: il2cpp_field_static_set_value");
        *(void**)(&field_set_value_object) = GetProcAddress(module, "il2cpp_field_set_value_object");
        LOG("Loaded: il2cpp_field_set_value_object");
        *(void**)(&gc_collect) = GetProcAddress(module, "il2cpp_gc_collect");
        LOG("Loaded: il2cpp_gc_collect");
        *(void**)(&gc_collect_a_little) = GetProcAddress(module, "il2cpp_gc_collect_a_little");
        LOG("Loaded: il2cpp_gc_collect_a_little");
        *(void**)(&gc_disable) = GetProcAddress(module, "il2cpp_gc_disable");
        LOG("Loaded: il2cpp_gc_disable");
        *(void**)(&gc_enable) = GetProcAddress(module, "il2cpp_gc_enable");
        LOG("Loaded: il2cpp_gc_enable");
        *(void**)(&gc_is_disabled) = GetProcAddress(module, "il2cpp_gc_is_disabled");
        LOG("Loaded: il2cpp_gc_is_disabled");
        *(void**)(&gc_get_used_size) = GetProcAddress(module, "il2cpp_gc_get_used_size");
        LOG("Loaded: il2cpp_gc_get_used_size");
        *(void**)(&gc_get_heap_size) = GetProcAddress(module, "il2cpp_gc_get_heap_size");
        LOG("Loaded: il2cpp_gc_get_heap_size");
        *(void**)(&gc_wbarrier_set_field) = GetProcAddress(module, "il2cpp_gc_wbarrier_set_field");
        LOG("Loaded: il2cpp_gc_wbarrier_set_field");
        *(void**)(&gchandle_new) = GetProcAddress(module, "il2cpp_gchandle_new");
        LOG("Loaded: il2cpp_gchandle_new");
        *(void**)(&gchandle_new_weakref) = GetProcAddress(module, "il2cpp_gchandle_new_weakref");
        LOG("Loaded: il2cpp_gchandle_new_weakref");
        *(void**)(&gchandle_get_target) = GetProcAddress(module, "il2cpp_gchandle_get_target ");
        LOG("Loaded: il2cpp_gchandle_get_target ");
        *(void**)(&gchandle_free) = GetProcAddress(module, "il2cpp_gchandle_free");
        LOG("Loaded: il2cpp_gchandle_free");
        *(void**)(&unity_liveness_calculation_begin) = GetProcAddress(module, "il2cpp_unity_liveness_calculation_begin");
        LOG("Loaded: il2cpp_unity_liveness_calculation_begin");
        *(void**)(&unity_liveness_calculation_end) = GetProcAddress(module, "il2cpp_unity_liveness_calculation_end");
        LOG("Loaded: il2cpp_unity_liveness_calculation_end");
        *(void**)(&unity_liveness_calculation_from_root) = GetProcAddress(module, "il2cpp_unity_liveness_calculation_from_root");
        LOG("Loaded: il2cpp_unity_liveness_calculation_from_root");
        *(void**)(&unity_liveness_calculation_from_statics) = GetProcAddress(module, "il2cpp_unity_liveness_calculation_from_statics");
        LOG("Loaded: il2cpp_unity_liveness_calculation_from_statics");
        *(void**)(&method_get_return_type) = GetProcAddress(module, "il2cpp_method_get_return_type");
        LOG("Loaded: il2cpp_method_get_return_type");
        *(void**)(&method_get_declaring_type) = GetProcAddress(module, "il2cpp_method_get_declaring_type");
        LOG("Loaded: il2cpp_method_get_declaring_type");
        *(void**)(&method_get_name) = GetProcAddress(module, "il2cpp_method_get_name");
        LOG("Loaded: il2cpp_method_get_name");
        *(void**)(&method_get_from_reflection) = GetProcAddress(module, "il2cpp_method_get_from_reflection");
        LOG("Loaded: il2cpp_method_get_from_reflection");
        *(void**)(&method_get_object) = GetProcAddress(module, "il2cpp_method_get_object");
        LOG("Loaded: il2cpp_method_get_object");
        *(void**)(&method_is_generic) = GetProcAddress(module, "il2cpp_method_is_generic");
        LOG("Loaded: il2cpp_method_is_generic");
        *(void**)(&method_is_inflated) = GetProcAddress(module, "il2cpp_method_is_inflated");
        LOG("Loaded: il2cpp_method_is_inflated");
        *(void**)(&method_is_instance) = GetProcAddress(module, "il2cpp_method_is_instance");
        LOG("Loaded: il2cpp_method_is_instance");
        *(void**)(&method_get_param_count) = GetProcAddress(module, "il2cpp_method_get_param_count");
        LOG("Loaded: il2cpp_method_get_param_count");
        *(void**)(&method_get_param) = GetProcAddress(module, "il2cpp_method_get_param");
        LOG("Loaded: il2cpp_method_get_param");
        *(void**)(&method_get_class) = GetProcAddress(module, "il2cpp_method_get_class");
        LOG("Loaded: il2cpp_method_get_class");
        *(void**)(&method_has_attribute) = GetProcAddress(module, "il2cpp_method_has_attribute");
        LOG("Loaded: il2cpp_method_has_attribute");
        *(void**)(&method_get_flags) = GetProcAddress(module, "il2cpp_method_get_flags");
        LOG("Loaded: il2cpp_method_get_flags");
        *(void**)(&method_get_token) = GetProcAddress(module, "il2cpp_method_get_token");
        LOG("Loaded: il2cpp_method_get_token");
        *(void**)(&method_get_param_name) = GetProcAddress(module, "il2cpp_method_get_param_name");
        LOG("Loaded: il2cpp_method_get_param_name");
        *(void**)(&profiler_install) = GetProcAddress(module, "il2cpp_profiler_install");
        LOG("Loaded: il2cpp_profiler_install");
        *(void**)(&profiler_set_events) = GetProcAddress(module, "il2cpp_profiler_set_events");
        LOG("Loaded: il2cpp_profiler_set_events");
        *(void**)(&profiler_install_enter_leave) = GetProcAddress(module, "il2cpp_profiler_install_enter_leave");
        LOG("Loaded: il2cpp_profiler_install_enter_leave");
        *(void**)(&profiler_install_allocation) = GetProcAddress(module, "il2cpp_profiler_install_allocation");
        LOG("Loaded: il2cpp_profiler_install_allocation");
        *(void**)(&profiler_install_gc) = GetProcAddress(module, "il2cpp_profiler_install_gc");
        LOG("Loaded: il2cpp_profiler_install_gc");
        *(void**)(&profiler_install_fileio) = GetProcAddress(module, "il2cpp_profiler_install_fileio");
        LOG("Loaded: il2cpp_profiler_install_fileio");
        *(void**)(&profiler_install_thread) = GetProcAddress(module, "il2cpp_profiler_install_thread");
        LOG("Loaded: il2cpp_profiler_install_thread");
        *(void**)(&property_get_flags) = GetProcAddress(module, "il2cpp_property_get_flags");
        LOG("Loaded: il2cpp_property_get_flags");
        *(void**)(&property_get_get_method) = GetProcAddress(module, "il2cpp_property_get_get_method");
        LOG("Loaded: il2cpp_property_get_get_method");
        *(void**)(&property_get_set_method) = GetProcAddress(module, "il2cpp_property_get_set_method");
        LOG("Loaded: il2cpp_property_get_set_method");
        *(void**)(&property_get_name) = GetProcAddress(module, "il2cpp_property_get_name");
        LOG("Loaded: il2cpp_property_get_name");
        *(void**)(&property_get_parent) = GetProcAddress(module, "il2cpp_property_get_parent");
        LOG("Loaded: il2cpp_property_get_parent");
        *(void**)(&object_get_class) = GetProcAddress(module, "il2cpp_object_get_class");
        LOG("Loaded: il2cpp_object_get_class");
        *(void**)(&object_get_size) = GetProcAddress(module, "il2cpp_object_get_size");
        LOG("Loaded: il2cpp_object_get_size");
        *(void**)(&object_get_virtual_method) = GetProcAddress(module, "il2cpp_object_get_virtual_method");
        LOG("Loaded: il2cpp_object_get_virtual_method");
        *(void**)(&object_new) = GetProcAddress(module, "il2cpp_object_new");
        LOG("Loaded: il2cpp_object_new");
        *(void**)(&object_unbox) = GetProcAddress(module, "il2cpp_object_unbox");
        LOG("Loaded: il2cpp_object_unbox");
        *(void**)(&value_box) = GetProcAddress(module, "il2cpp_value_box");
        LOG("Loaded: il2cpp_value_box");
        *(void**)(&monitor_enter) = GetProcAddress(module, "il2cpp_monitor_enter");
        LOG("Loaded: il2cpp_monitor_enter");
        *(void**)(&monitor_try_enter) = GetProcAddress(module, "il2cpp_monitor_try_enter");
        LOG("Loaded: il2cpp_monitor_try_enter");
        *(void**)(&monitor_exit) = GetProcAddress(module, "il2cpp_monitor_exit");
        LOG("Loaded: il2cpp_monitor_exit");
        *(void**)(&monitor_pulse) = GetProcAddress(module, "il2cpp_monitor_pulse");
        LOG("Loaded: il2cpp_monitor_pulse");
        *(void**)(&monitor_pulse_all) = GetProcAddress(module, "il2cpp_monitor_pulse_all");
        LOG("Loaded: il2cpp_monitor_pulse_all");
        *(void**)(&monitor_wait) = GetProcAddress(module, "il2cpp_monitor_wait");
        LOG("Loaded: il2cpp_monitor_wait");
        *(void**)(&monitor_try_wait) = GetProcAddress(module, "il2cpp_monitor_try_wait");
        LOG("Loaded: il2cpp_monitor_try_wait");
        *(void**)(&runtime_invoke) = GetProcAddress(module, "il2cpp_runtime_invoke");
        LOG("Loaded: il2cpp_runtime_invoke");
        *(void**)(&runtime_invoke_convert_args) = GetProcAddress(module, "il2cpp_runtime_invoke_convert_args");
        LOG("Loaded: il2cpp_runtime_invoke_convert_args");
        *(void**)(&runtime_class_init) = GetProcAddress(module, "il2cpp_runtime_class_init");
        LOG("Loaded: il2cpp_runtime_class_init");
        *(void**)(&runtime_object_init) = GetProcAddress(module, "il2cpp_runtime_object_init");
        LOG("Loaded: il2cpp_runtime_object_init");
        *(void**)(&runtime_object_init_exception) = GetProcAddress(module, "il2cpp_runtime_object_init_exception");
        LOG("Loaded: il2cpp_runtime_object_init_exception");
        *(void**)(&runtime_unhandled_exception_policy_set) = GetProcAddress(module, "il2cpp_runtime_unhandled_exception_policy_set");
        LOG("Loaded: il2cpp_runtime_unhandled_exception_policy_set");
        *(void**)(&string_length) = GetProcAddress(module, "il2cpp_string_length");
        LOG("Loaded: il2cpp_string_length");
        *(void**)(&string_chars) = GetProcAddress(module, "il2cpp_string_chars");
        LOG("Loaded: il2cpp_string_chars");
        *(void**)(&string_new) = GetProcAddress(module, "il2cpp_string_new");
        LOG("Loaded: il2cpp_string_new");
        *(void**)(&string_new_len) = GetProcAddress(module, "il2cpp_string_new_len");
        LOG("Loaded: il2cpp_string_new_len");
        *(void**)(&string_new_utf16) = GetProcAddress(module, "il2cpp_string_new_utf16");
        LOG("Loaded: il2cpp_string_new_utf16");
        *(void**)(&string_new_wrapper) = GetProcAddress(module, "il2cpp_string_new_wrapper");
        LOG("Loaded: il2cpp_string_new_wrapper");
        *(void**)(&string_intern) = GetProcAddress(module, "il2cpp_string_intern");
        LOG("Loaded: il2cpp_string_intern");
        *(void**)(&string_is_interned) = GetProcAddress(module, "il2cpp_string_is_interned");
        LOG("Loaded: il2cpp_string_is_interned");
        *(void**)(&thread_current) = GetProcAddress(module, "il2cpp_thread_current");
        LOG("Loaded: il2cpp_thread_current");
        *(void**)(&thread_attach) = GetProcAddress(module, "il2cpp_thread_attach");
        LOG("Loaded: il2cpp_thread_attach");
        *(void**)(&thread_detach) = GetProcAddress(module, "il2cpp_thread_detach");
        LOG("Loaded: il2cpp_thread_detach");
        *(void**)(&thread_get_all_attached_threads) = GetProcAddress(module, "il2cpp_thread_get_all_attached_threads");
        LOG("Loaded: il2cpp_thread_get_all_attached_threads");
        *(void**)(&is_vm_thread) = GetProcAddress(module, "il2cpp_is_vm_thread");
        LOG("Loaded: il2cpp_is_vm_thread");
        *(void**)(&current_thread_walk_frame_stack) = GetProcAddress(module, "il2cpp_current_thread_walk_frame_stack");
        LOG("Loaded: il2cpp_current_thread_walk_frame_stack");
        *(void**)(&thread_walk_frame_stack) = GetProcAddress(module, "il2cpp_thread_walk_frame_stack");
        LOG("Loaded: il2cpp_thread_walk_frame_stack");
        *(void**)(&current_thread_get_top_frame) = GetProcAddress(module, "il2cpp_current_thread_get_top_frame");
        LOG("Loaded: il2cpp_current_thread_get_top_frame");
        *(void**)(&thread_get_top_frame) = GetProcAddress(module, "il2cpp_thread_get_top_frame");
        LOG("Loaded: il2cpp_thread_get_top_frame");
        *(void**)(&current_thread_get_frame_at) = GetProcAddress(module, "il2cpp_current_thread_get_frame_at");
        LOG("Loaded: il2cpp_current_thread_get_frame_at");
        *(void**)(&thread_get_frame_at) = GetProcAddress(module, "il2cpp_thread_get_frame_at");
        LOG("Loaded: il2cpp_thread_get_frame_at");
        *(void**)(&current_thread_get_stack_depth) = GetProcAddress(module, "il2cpp_current_thread_get_stack_depth");
        LOG("Loaded: il2cpp_current_thread_get_stack_depth");
        *(void**)(&thread_get_stack_depth) = GetProcAddress(module, "il2cpp_thread_get_stack_depth");
        LOG("Loaded: il2cpp_thread_get_stack_depth");
        *(void**)(&type_get_object) = GetProcAddress(module, "il2cpp_type_get_object");
        LOG("Loaded: il2cpp_type_get_object");
        *(void**)(&type_get_type) = GetProcAddress(module, "il2cpp_type_get_type");
        LOG("Loaded: il2cpp_type_get_type");
        *(void**)(&type_get_class_or_element_class) = GetProcAddress(module, "il2cpp_type_get_class_or_element_class");
        LOG("Loaded: il2cpp_type_get_class_or_element_class");
        *(void**)(&type_get_name) = GetProcAddress(module, "il2cpp_type_get_name");
        LOG("Loaded: il2cpp_type_get_name");
        *(void**)(&type_is_byref) = GetProcAddress(module, "il2cpp_type_is_byref");
        LOG("Loaded: il2cpp_type_is_byref");
        *(void**)(&type_get_attrs) = GetProcAddress(module, "il2cpp_type_get_attrs");
        LOG("Loaded: il2cpp_type_get_attrs");
        *(void**)(&type_equals) = GetProcAddress(module, "il2cpp_type_equals");
        LOG("Loaded: il2cpp_type_equals");
        *(void**)(&type_get_assembly_qualified_name) = GetProcAddress(module, "il2cpp_type_get_assembly_qualified_name");
        LOG("Loaded: il2cpp_type_get_assembly_qualified_name");
        *(void**)(&image_get_assembly) = GetProcAddress(module, "il2cpp_image_get_assembly");
        LOG("Loaded: il2cpp_image_get_assembly");
        *(void**)(&image_get_name) = GetProcAddress(module, "il2cpp_image_get_name");
        LOG("Loaded: il2cpp_image_get_name");
        *(void**)(&image_get_filename) = GetProcAddress(module, "il2cpp_image_get_filename");
        LOG("Loaded: il2cpp_image_get_filename");
        *(void**)(&image_get_entry_point) = GetProcAddress(module, "il2cpp_image_get_entry_point");
        LOG("Loaded: il2cpp_image_get_entry_point");
        *(void**)(&image_get_class_count) = GetProcAddress(module, "il2cpp_image_get_class_count");
        LOG("Loaded: il2cpp_image_get_class_count");
        *(void**)(&image_get_class) = GetProcAddress(module, "il2cpp_image_get_class");
        LOG("Loaded: il2cpp_image_get_class");
        *(void**)(&capture_memory_snapshot) = GetProcAddress(module, "il2cpp_capture_memory_snapshot");
        LOG("Loaded: il2cpp_capture_memory_snapshot");
        *(void**)(&free_captured_memory_snapshot) = GetProcAddress(module, "il2cpp_free_captured_memory_snapshot");
        LOG("Loaded: il2cpp_free_captured_memory_snapshot");
        *(void**)(&set_find_plugin_callback) = GetProcAddress(module, "il2cpp_set_find_plugin_callback");
        LOG("Loaded: il2cpp_set_find_plugin_callback");
        *(void**)(&register_log_callback) = GetProcAddress(module, "il2cpp_register_log_callback");
        LOG("Loaded: il2cpp_register_log_callback");
        *(void**)(&debugger_set_agent_options) = GetProcAddress(module, "il2cpp_debugger_set_agent_options");
        LOG("Loaded: il2cpp_debugger_set_agent_options");
        *(void**)(&is_debugger_attached) = GetProcAddress(module, "il2cpp_is_debugger_attached");
        LOG("Loaded: il2cpp_is_debugger_attached");
        *(void**)(&unity_install_unitytls_interface) = GetProcAddress(module, "il2cpp_unity_install_unitytls_interface");
        LOG("Loaded: il2cpp_unity_install_unitytls_interface");
        *(void**)(&custom_attrs_from_class) = GetProcAddress(module, "il2cpp_custom_attrs_from_class");
        LOG("Loaded: il2cpp_custom_attrs_from_class");
        *(void**)(&custom_attrs_from_method) = GetProcAddress(module, "il2cpp_custom_attrs_from_method");
        LOG("Loaded: il2cpp_custom_attrs_from_method");
        *(void**)(&custom_attrs_get_attr) = GetProcAddress(module, "il2cpp_custom_attrs_get_attr");
        LOG("Loaded: il2cpp_custom_attrs_get_attr");
        *(void**)(&custom_attrs_has_attr) = GetProcAddress(module, "il2cpp_custom_attrs_has_attr");
        LOG("Loaded: il2cpp_custom_attrs_has_attr");
        *(void**)(&custom_attrs_construct) = GetProcAddress(module, "il2cpp_custom_attrs_construct");
        LOG("Loaded: il2cpp_custom_attrs_construct");
        *(void**)(&custom_attrs_free) = GetProcAddress(module, "il2cpp_custom_attrs_free");
        LOG("Loaded: il2cpp_custom_attrs_free");

	}
}
