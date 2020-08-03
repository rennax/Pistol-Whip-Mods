#include "Messenger.hpp"


namespace Messenger
{
	void Send(Messages::LevelSelectEvent e)
	{
		Il2CppClass* klass = il2cpp_utils::GetClassFromName("", "Messages/LevelSelectEvent");
		Il2CppObject* obj = il2cpp_functions::object_new(klass);
		il2cpp_utils::RunMethod(obj, ".ctor");
		il2cpp_utils::RunMethod(obj, "Set", e.level);


		//TODO figure out how the messenger works, so we can use that instead of calling
		//objects individually
		klass = il2cpp_utils::GetClassFromName("UnityEngine", "Object");
		Il2CppArray* objects = nullptr;
		auto type = il2cpp_functions::type_get_object(
			il2cpp_functions::class_get_type_const(
				il2cpp_utils::GetClassFromName("", "LevelSelectTrigger")
			)
		);
		if (!il2cpp_utils::RunMethod(&objects, klass, "FindObjectsOfType", type))
		{
			LOG("WARNING: Failed call to Objects.FindObjectsOfType(Type) in Messenger::Send\n");
			return;
		}
		LOG("TODO rest of Send(Messenger.Send(LevelSelectEvent))\n");

		//klass = il2cpp_utils::GetClassFromName("", "Messenger");
		//Il2CppObject* messenger = nullptr;
		//il2cpp_utils::RunMethod(&messenger, klass, "get_Default");

		////il2cpp_utils::RunMethod(messenger, "Send<CheevoMessage>", obj);

		//const MethodInfo* info = il2cpp_utils::GetMethod("", "Messenger", "Send", 1);
		//// Get my generic methodInfo
		//info = il2cpp_utils::MakeGeneric(info, { il2cpp_utils::GetClassFromName("", "Messages/LevelSelectEvent") });
		//// Call the method
		//if (!il2cpp_utils::RunMethod(messenger, info, obj))
		//	LOG("WARNING: Failed to run Send(Messages.LevelSelectEvent e)\n");
	}
	


};