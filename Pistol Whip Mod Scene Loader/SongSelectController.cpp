#include "SongSelectController.hpp"
#include "AssetBundle.hpp"
#include "GameObject.hpp"
#include <functional>


Il2CppObject* SongSelectController::Add_CHUIButtonTrigger(Il2CppObject* gameObject)
{
	auto actionType = il2cpp_functions::class_get_type_const(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction"));

	void* n = nullptr;
	Il2CppObject* actionEnter = il2cpp_utils::MakeAction(actionType, this, OnEnter);
	Il2CppObject* actionStay = il2cpp_utils::MakeAction(actionType, this, OnStay);
	Il2CppObject* actionExit = il2cpp_utils::MakeAction(actionType, this, OnExit);
	Il2CppObject* actionClick = il2cpp_utils::MakeAction(actionType, this, OnClick);


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
	Il2CppObject* tmpGO;
	il2cpp_utils::RunMethod(&tmpGO, songPanelButton, "Find", il2cpp_utils::createcsstr("TextMeshPro Text"));
	tmpProText = GameObject::GetComponent(tmpGO, "TMPro", "TMP_Text");
	Add_CHUIButtonTrigger(self);
	

}

SongSelectController::~SongSelectController()
{
}

//void SongSelectController::CallMe()
//{
//	LOG("\nYou pressed a button\n\n!");
//}
//
void SongSelectController::OnClick(void* self)
{
	SongSelectController* ssc = static_cast<SongSelectController*>(self);
	if (ssc != nullptr)
	{
		ssc->SetText("Clicked!");

	}
	LOG("SongSelectController::OnClick()!\n");
}

void SongSelectController::SetText(std::string text)
{
	static auto tmp_text_class = il2cpp_utils::GetClassFromName("TMPro", "TMP_Text");
	static auto get_text_method = il2cpp_utils::GetMethod(tmp_text_class, "get_text", 0);
	static auto set_text_method = il2cpp_utils::GetMethod(tmp_text_class, "set_text", 1);
	static auto set_richText_method = il2cpp_utils::GetMethod(tmp_text_class, "set_richText", 1);

	il2cpp_utils::RunMethod(tmpProText, set_text_method, il2cpp_utils::createcsstr(text));
}

void SongSelectController::OnEnter(void* self)
{
	SongSelectController* ssc = static_cast<SongSelectController*>(self);

	LOG("SongSelectController::OnEnter()!\n");
}

static bool stayCalledOnce = false;

void SongSelectController::OnExit(void* self)
{
	SongSelectController* ssc = static_cast<SongSelectController*>(self);
	LOG("SongSelectController::OnExit()!\n");
	stayCalledOnce = false;
}

void SongSelectController::OnStay(void* self)
{
	if (!stayCalledOnce)
	{
		SongSelectController* ssc = static_cast<SongSelectController*>(self);
		LOG("SongSelectController::OnStay()!\n");
		stayCalledOnce = true;
	}
}



//void OnClick()
//{
//	LOG("SongSelectController::OnClick()!\n");
//}
//
//void OnEnter()
//{
//	LOG("SongSelectController::OnEnter()!\n");
//}
//
//void OnExit()
//{
//	LOG("SongSelectController::OnExit()!\n");
//}
//
//void OnStay()
//{
//	LOG("SongSelectController::OnStay()!\n");
//}
