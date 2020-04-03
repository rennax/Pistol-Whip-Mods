#ifndef CSHARPLIST_HPP
#define CSHARPLIST_HPP

#include "il2cpp_utils.hpp"

namespace CSharp {

	template<typename T>
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
			itemGetMethod = il2cpp_utils::GetPropertyGetMethod(instance->klass, "Item");
			countGetMethod = il2cpp_utils::GetPropertyGetMethod(instance->klass, "Count");
			
			addMethod = il2cpp_utils::GetMethod(instance->klass, "Add", 1);
		}
	public:
		//TODO: Create a new list
		//Doesn't work, as it needs to create a generic type and is currently not setup for this
		List() 
		{
			const Il2CppClass* klass = il2cpp_utils::GetClassFromName("System.Collections.Generic", "List`1");
			instance = il2cpp_functions::object_new(klass);
			LOG("Created instance of List<T> object");
			init();
		}
		//Create list from existing instance
		List(Il2CppObject* instance_) : instance(instance_)
		{
			init();
		}

		Il2CppObject* getInstance() {
			return instance;
		}
		
		T operator[](std::size_t idx)
		{
			T obj;
			if (!il2cpp_utils::RunMethod(&obj, instance, itemGetMethod, &idx))
			{
				LOG("Failed to call to List<>.Item[]\n");
			}
			return obj;
		}

		template<typename T>
		bool Add(T obj)
		{
			if (!il2cpp_utils::RunMethod(instance, addMethod, &obj))
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
