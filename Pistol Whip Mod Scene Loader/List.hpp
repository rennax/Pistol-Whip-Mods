#ifndef CSHARPLIST_HPP
#define CSHARPLIST_HPP

#include "il2cpp_utils.hpp"

namespace CSharp {


	class List {
	private:
		Il2CppObject* instance;
		const MethodInfo* itemGetMethod;
		const MethodInfo* itemSetMethod;
		const MethodInfo* addMethod;
		const MethodInfo* countGetMethod;

		void init()
		{
			//Init properties
			const PropertyInfo* itemProp = il2cpp_functions::class_get_property_from_name(instance->klass, "Item");
			itemGetMethod = il2cpp_functions::property_get_get_method(itemProp);
			const PropertyInfo* countProp = il2cpp_functions::class_get_property_from_name(instance->klass, "Count");
			countGetMethod = il2cpp_functions::property_get_get_method(countProp);
			
			addMethod = il2cpp_utils::GetMethod(instance->klass, "Add", 1);
		}
	public:
		List() {}
		List(Il2CppObject* instance_) : instance(instance_)
		{
			init();
		}

		void init(Il2CppObject* instance_)
		{
			instance = instance_;
			init();
		}

		Il2CppObject* operator[](std::size_t idx)
		{
			Il2CppObject* obj = nullptr;
			if (!il2cpp_utils::RunMethod(&obj, instance, itemGetMethod, &idx))
			{
				LOG("Failed to call to List<>.Item[]\n");
			}
			return obj;
		}

		bool Add(Il2CppObject* obj)
		{
			if (!il2cpp_utils::RunMethod(instance, addMethod, obj))
			{
				LOG("Failed to call to List<>.Add(...)\n");
				return false;
			}
			return true;
		}

		uint32_t Count() 
		{
			uint32_t count = -1;
			if (!il2cpp_utils::RunMethod(&count, instance, countGetMethod))
			{
				LOG("Failed to call to List<>.Count\n");
				return count;
			}
			return count;
		}
	};

};

#endif // !CSHARPLIST_HPP
