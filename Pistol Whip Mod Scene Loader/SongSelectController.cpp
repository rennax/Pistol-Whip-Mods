#include "SongSelectController.hpp"
#include "AssetBundle.hpp"
#include "GameObject.hpp"
#include <functional>
#include <fstream>


SongSelectController* SongSelectController::_instance = nullptr;

Il2CppObject* SongSelectController::Add_CHUIButtonTrigger(Il2CppObject* gameObject)
{
	auto actionType = il2cpp_functions::class_get_type_const(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction"));
	void* n = nullptr;
	//UnityActions
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
	il2cpp_utils::SetFieldValue(enterTrigger, "hoverEnterEvent", hoverEnterEvent);
	Il2CppObject* stayTrigger = GameObject::AddComponent(gameObject, "", "CHUIButtonSimple");
	il2cpp_utils::SetFieldValue(stayTrigger, "hoverStayEvent", hoverStayEvent);
	Il2CppObject* exitTrigger = GameObject::AddComponent(gameObject, "", "CHUIButtonSimple");
	il2cpp_utils::SetFieldValue(exitTrigger, "hoverExitEvent", hoverExitEvent);
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

void SongSelectController::CreateLevelData()
{
	std::ifstream i("Custom Levels/x02/level.json");
	json j;
	i >> j;
	//std::string s = j.dump();
	//LOG("%s\n", s.c_str());


	int32_t diff = 0;
	il2cpp_utils::SetFieldValue(gameManager, "difficulty", &diff);

	std::string version = j["version"];
	LOG("%s\n", version.c_str());
	levelData = data.Load(j["levelData"]);
}

Il2CppObject* SongSelectController::GetGameMap(Difficulty difficulty)
{
	Il2CppObject* levels = il2cpp_utils::GetFieldValue(gameManager, "levels");
	Il2CppObject* lastReleasedScene = il2cpp_utils::GetFieldValue(levels, "lastReleasedScene");
	il2cpp_utils::SetFieldValue(levelData, "songSwitch", il2cpp_utils::GetFieldValue(lastReleasedScene, "songSwitch"));
	Il2CppArray* maps = reinterpret_cast<Il2CppArray*>(il2cpp_utils::GetFieldValue(levelData, "maps"));
	Il2CppObject* map = il2cpp_array_get(maps, Il2CppObject*, static_cast<int32_t>(difficulty)); //GameMap
	return map;
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


	if (!il2cpp_utils::GetFieldValue(&gameManager, il2cpp_utils::GetClassFromName("", "GameManager"), "s_instance"))
		LOG("WARNING: Failed to get instance of GameManager\n");
	
	CreateLevelData();

}

SongSelectController::~SongSelectController()
{
}


void SongSelectController::OnClick()
{
	SongSelectController* ssc = SongSelectController::get_Instance();
	if (ssc != nullptr)
	{
		ssc->SetText("Clicked!");
		static auto gmClass = il2cpp_utils::GetClassFromName("", "GameManager");
		static auto setLevelInternal = il2cpp_utils::GetMethod(gmClass, "SetLevelInternal", 1);
		static auto getDifficulty = il2cpp_utils::GetMethod(gmClass, "GetDifficulty", 0);
		Difficulty diff;
		il2cpp_utils::RunMethod(&diff, gmClass, getDifficulty);
		il2cpp_utils::RunMethod(gmClass, setLevelInternal, ssc->GetGameMap(diff));
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

SongSelectController* SongSelectController::get_Instance()
{
	if (SongSelectController::_instance == nullptr)
	{
		SongSelectController::_instance = new SongSelectController();
	}

	return SongSelectController::_instance;
}

void SongSelectController::OnEnter(SongSelectController* self)
{
	LOG("SongSelectController::OnEnter()!\n");
}

static bool stayCalledOnce = false;

void SongSelectController::OnExit(SongSelectController* self)
{;
	LOG("SongSelectController::OnExit()!\n");
	stayCalledOnce = false;
}

void SongSelectController::OnStay(SongSelectController* self)
{
	if (stayCalledOnce == false)
	{
		LOG("SongSelectController::OnStay()!\n");
		stayCalledOnce = true;
	}
}

