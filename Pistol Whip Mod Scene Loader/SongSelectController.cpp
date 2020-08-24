#include "SongSelectController.hpp"
#include "AssetBundle.hpp"
#include "GameObject.hpp"
#include <functional>


Il2CppObject* SongSelectController::Add_CHUIButtonTrigger(Il2CppObject* gameObject)
{
	auto actionType = il2cpp_functions::class_get_type_const(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction"));

	void* n = nullptr;
	Il2CppObject* actionEnter = il2cpp_utils::MakeAction(actionType, n, OnEnter);
	Il2CppObject* actionStay = il2cpp_utils::MakeAction(actionType, n, OnStay);
	Il2CppObject* actionExit = il2cpp_utils::MakeAction(actionType, n, OnExit);
	Il2CppObject* actionClick = il2cpp_utils::MakeAction(actionType, n, OnClick);


	//UnityEvents
	Il2CppObject* eventEnter = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityEvent"));
	il2cpp_utils::RunMethod(eventEnter, ".ctor");
	il2cpp_utils::RunMethod(eventEnter, "AddListener", actionEnter);
	Il2CppObject* eventStay = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityEvent"));
	il2cpp_utils::RunMethod(eventStay, ".ctor");
	il2cpp_utils::RunMethod(eventStay, "AddListener", actionStay);
	Il2CppObject* eventExit = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityEvent"));
	il2cpp_utils::RunMethod(eventExit, ".ctor");
	il2cpp_utils::RunMethod(eventExit, "AddListener", actionExit);
	Il2CppObject* eventClick = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityEvent"));
	il2cpp_utils::RunMethod(eventClick, ".ctor");
	il2cpp_utils::RunMethod(eventClick, "AddListener", actionClick);

	//UnityEventTriggers
	Il2CppObject* hoverEnterEvent = GameObject::AddComponent(gameObject, "", "UnityEventTrigger");
	il2cpp_utils::SetFieldValue(hoverEnterEvent, "Event", eventEnter);
	Il2CppObject* hoverStayEvent = GameObject::AddComponent(gameObject, "", "UnityEventTrigger");
	il2cpp_utils::SetFieldValue(hoverStayEvent, "Event", eventStay);
	Il2CppObject* hoverExitEvent = GameObject::AddComponent(gameObject, "", "UnityEventTrigger");
	il2cpp_utils::SetFieldValue(hoverExitEvent, "Event", eventExit);
	Il2CppObject* clickEvent = GameObject::AddComponent(gameObject, "", "UnityEventTrigger");
	il2cpp_utils::SetFieldValue(clickEvent, "Event", eventClick);

	//CHUIButtonTrigger
	Il2CppObject* enterTrigger = GameObject::AddComponent(gameObject, "", "CHUIButtonSimple");
	il2cpp_utils::SetFieldValue(enterTrigger, "clickEvent", hoverEnterEvent);
	Il2CppObject* stayTrigger = GameObject::AddComponent(gameObject, "", "CHUIButtonSimple");
	il2cpp_utils::SetFieldValue(stayTrigger, "clickEvent", hoverStayEvent);
	Il2CppObject* exitTrigger = GameObject::AddComponent(gameObject, "", "CHUIButtonSimple");
	il2cpp_utils::SetFieldValue(exitTrigger, "clickEvent", hoverExitEvent);
	Il2CppObject* clickTrigger = GameObject::AddComponent(gameObject, "", "CHUIButtonSimple");
	il2cpp_utils::SetFieldValue(clickTrigger, "clickEvent", clickEvent);

	//CHUI_CHUITriggerAdapterEvent
	Il2CppObject* enterAdapter = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "CHUI_CHUITriggerAdapterEvent"));
	il2cpp_utils::RunMethod(enterAdapter, ".ctor", enterTrigger);
	Il2CppObject* stayAdapter = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "CHUI_CHUITriggerAdapterEvent"));
	il2cpp_utils::RunMethod(stayAdapter, ".ctor", stayTrigger);
	Il2CppObject* exitAdapter = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "CHUI_CHUITriggerAdapterEvent"));
	il2cpp_utils::RunMethod(exitAdapter, ".ctor", exitTrigger);
	Il2CppObject* clickAdapter = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("", "CHUI_CHUITriggerAdapterEvent"));
	il2cpp_utils::RunMethod(clickAdapter, ".ctor", clickTrigger);

	//CHUI_TriggerEvents
	Il2CppObject* lastButtonTrigger = GameObject::AddComponent(gameObject, "", "CHUI_TriggerEvents");
	il2cpp_utils::SetFieldValue(lastButtonTrigger, "hoverEnterEvent", enterAdapter);
	il2cpp_utils::SetFieldValue(lastButtonTrigger, "hoverStayEvent", stayAdapter);
	il2cpp_utils::SetFieldValue(lastButtonTrigger, "hoverExitEvent", exitAdapter);
	il2cpp_utils::SetFieldValue(lastButtonTrigger, "clickEvent", clickAdapter);

	return lastButtonTrigger;
}

SongSelectController::SongSelectController()
{
	Il2CppObject* assetDB = AssetBundle::LoadFromFile("Mods/Pistol Whip Mod Scene Loader Assets");
	Il2CppObject* songSelectController = AssetBundle::LoadAsset(assetDB, "SongSelector3D");
	Il2CppObject* toInstantiate = AssetBundle::LoadAsset(assetDB, "SongSelectController");

	Vector3 position = { 2, 1, 2 };
	Quaternion rotation = { -0.7071068, 0, 0, 0.7071068 };
	il2cpp_utils::RunMethod(&self, il2cpp_utils::GetClassFromName("UnityEngine", "GameObject"), "Instantiate", toInstantiate, &position, &rotation);
	il2cpp_utils::RunMethod(&canvas, self, "Find", il2cpp_utils::createcsstr("Canvas"));
	il2cpp_utils::RunMethod(&songPanelButton, canvas, "Find", il2cpp_utils::createcsstr("Button"));
	
	Add_CHUIButtonTrigger(self);
	

	//bool active = false;
	//il2cpp_utils::RunMethod(songPanelButton, "SetActive", &active);

	////GameObject::AddComponent(canvas, il2cpp_utils::GetClassFromName("", "OVRRaycaster"));
	//auto el = GameObject::InstantiateEmpty({ 0,0,0 }, { 0,0,0,0 });
	//auto transformProp = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject"), "transform");
	//Il2CppObject* uiTransform, canvasTransform;
	//il2cpp_utils::RunMethod(&uiTransform, el, transformProp);
	//il2cpp_utils::RunMethod(&canvasTransform, canvas, transformProp);
	//il2cpp_utils::RunMethod(uiTransform, "SetParent", canvasTransform);
	//GameObject::AddComponent(el, il2cpp_utils::GetClassFromName("", "CHUI_Button"));

	//
	//class CHUI_TriggerEvents {
	//	
	//};

	//class CHUIButtonTrigger {

	//};
	//
	//class CHUI_CHUITriggerAdapterEvent {

	//};

	//Il2CppObject* action = il2cpp_functions::object_new(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction"));
	//il2cpp_utils::RunMethod(action, ".ctor", this, [this]() {CallMe(); });

	//auto btnType = GameObject::GetComponentType(songPanelButton, "UnityEngine.UI", "Button");
	//
	//Il2CppObject* button = nullptr;
	//il2cpp_utils::RunMethod(&button, songPanelButton, "GetComponent", btnType);
	//if (button == nullptr)
	//{
	//	LOG("Failed to get button son song select controller\n");
	//}

	//if (!il2cpp_utils::RunMethod(button, "set_onClick", action))
	//	LOG("Failed to set onClick action for UI\n");
}

SongSelectController::~SongSelectController()
{
}

//void SongSelectController::CallMe()
//{
//	LOG("\nYou pressed a button\n\n!");
//}
//
//void SongSelectController::OnClick()
//{
//	LOG("SongSelectController::OnClick()!\n");
//}

//void SongSelectController::OnEnter()
//{
//	LOG("SongSelectController::OnEnter()!\n");
//}

//void SongSelectController::OnExit()
//{
//	LOG("SongSelectController::OnExit()!\n");
//}
//
////void SongSelectController::OnStay()
////{
////	LOG("SongSelectController::OnStay()!\n");
////}



void OnClick()
{
	LOG("SongSelectController::OnClick()!\n");
}

void OnEnter()
{
	LOG("SongSelectController::OnEnter()!\n");
}

void OnExit()
{
	LOG("SongSelectController::OnExit()!\n");
}

void OnStay()
{
	LOG("SongSelectController::OnStay()!\n");
}
