#include "CustomLevelDatabase.hpp"
#include <filesystem>
#include "GameObject.hpp"
#include "Sprite.hpp"
#include <cmath>

namespace fs = std::filesystem;

CustomLevelDatabase::CustomLevelDatabase(Il2CppObject* controller) 
	: songSelectionUIController(controller),
	albumArtDB(il2cpp_utils::GetFieldValue(songSelectionUIController, "albumArtDB")) // yikes
{
	Il2CppObject* levelDatabase = il2cpp_utils::GetFieldValue(songSelectionUIController, "levelDB");
	il2cpp_utils::GetFieldValue(&highestLevelIndex, levelDatabase, "highestLevelIndex");
	LOG("HighestLevelIndex %u\n", highestLevelIndex);
	BuildDatabase();
	CreatePageIndicators(std::ceil((double)levels.size()/(double)songsPerPage));
	PopulateSongSelectionUI();
}

CustomLevelDatabase::~CustomLevelDatabase()
{
}

void CustomLevelDatabase::BuildDatabase()
{
	//Get all valid instances of custom levels
	for (auto& p : fs::directory_iterator(customLevelPath))
	{

		if (!p.is_directory()) continue;
		fs::path levelPath = p.path();
		levelPath.concat("/level.json");
		if (!p.exists()) continue;
		levels.push_back(Level(p));
	}

	for (auto& level : levels)
	{
		level.Load();
	}
}

void CustomLevelDatabase::PopulateSongSelectionUI()
{
	static auto gameObjectGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "gameObject");

	static auto parentTransformGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");
	static auto parentTransformSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");

	static auto positionGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "position");
	static auto positionSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "position");
	
	static auto spriteSetProperty = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine.UI", "Image"), "sprite");
	
	int32_t i = 0;
	int32_t startPage = 6;
	for (auto& level : levels)
	{
		Il2CppObject* panelToCopy;
		List<Il2CppObject*> songPanelUIControllerList(il2cpp_utils::GetFieldValue(songSelectionUIController, "songPanelUIControllerList"));
		il2cpp_utils::RunMethod(&panelToCopy, songPanelUIControllerList[16], gameObjectGet);
		Il2CppObject* panelGO = GameObject::Instantiate(panelToCopy);
		Il2CppObject* panel = GameObject::GetComponent(panelGO, "", "SongPanelUIController");

		Il2CppObject* panelToCopyTransform = GameObject::GetComponent(panelToCopy, "UnityEngine", "Transform");
		Il2CppObject* panelTransform = GameObject::GetComponent(panelGO, "UnityEngine", "Transform");

		Il2CppObject* parentToSet;
		il2cpp_utils::RunMethod(&parentToSet, panelToCopyTransform, parentTransformGet);
		il2cpp_utils::RunMethod(panelTransform, parentTransformSet, parentToSet);


		Vector3 position{ 8.88903f + (1.24001f * (i + 5)), 1.117992f, 5.039f };
		il2cpp_utils::RunMethod(panelTransform, positionSet, &position);

		int32_t panelChildCount;
		il2cpp_utils::GetFieldValue(&panelChildCount, songSelectionUIController, "panelChildCount");
		panelChildCount++;
		il2cpp_utils::SetFieldValue(songSelectionUIController, "panelChildCount", &panelChildCount);

		int32_t levelIndex = highestLevelIndex + i + 1; //otherwise first map is same as highestlevelindex
		il2cpp_utils::SetFieldValue(panel, "levelDataIndex", &levelIndex);

		//TODO: Create container class for Dictionary
		Il2CppObject* nameToPage;
		il2cpp_utils::GetFieldValue(&nameToPage, songSelectionUIController, "nameToPage");
		int32_t page = startPage + std::floor(i/songsPerPage);
		il2cpp_utils::RunMethod(nameToPage, "Add", level.GetSongName(), &page);


		Il2CppObject* songImage = il2cpp_utils::GetFieldValue(panel, "songImage"); // Image

		il2cpp_utils::RunMethod(songImage, spriteSetProperty, level.GetAlbumArt().art);

		
		albumArtDB.AddEntry(level.GetLevelData(), level.GetAlbumArt());
		i++;
	}
}

Level CustomLevelDatabase::GetLevelAtLevelIndex(uint32_t levelIndex)
{
	//to account for highestLevelIndex + i + 1
	return levels[levelIndex - highestLevelIndex - 1];
}

uint32_t CustomLevelDatabase::HighestLevelIndex()
{
	return highestLevelIndex;
}

void CustomLevelDatabase::CreatePageIndicators(uint32_t count)
{
	static auto parentPropertyGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "parent");
	static auto parentPropertySet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "parent");

	static auto parentTransformGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");
	static auto parentTransformSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Transform"), "parent");


	static auto gameObjectGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "gameObject");
	static auto transformGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "transform");


	static auto positionGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "position");
	static auto positionSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "position");

	static auto anchoredPositionGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition");
	static auto anchoredPositionSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition");

	static auto anchoredPosition3DGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition3D");
	static auto anchoredPosition3DSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchoredPosition3D");

	static auto offsetMinGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMin");
	static auto offsetMinSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMin");

	static auto offsetMaxGet = il2cpp_utils::GetPropertyGetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMax");
	static auto offsetMaxSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "offsetMax");

	static auto anchorMinSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchorMin");
	static auto anchorMaxSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "anchorMax");
	static auto pivotSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "pivot");
	static auto sizeDeltaSet = il2cpp_utils::GetPropertySetMethod(il2cpp_utils::GetClassFromName("UnityEngine", "RectTransform"), "sizeDelta");

	LOG("CustomLevelDatabase.CreatePageIndicators(): Creating %u page indicators\n", count);

	// Create new page indicator
	for (size_t i = 0; i < count; i++)
	{
		List<Il2CppObject*> pageCentersList(il2cpp_utils::GetFieldValue(songSelectionUIController, "pageCentersList"));
		Il2CppObject* centerListParent;
		il2cpp_utils::RunMethod(&centerListParent, pageCentersList[0], parentPropertyGet);

		Il2CppObject* centerObject = GameObject::InstantiateEmpty({ 0,0,0 }, { 0,0,0,0 });
		Il2CppObject* center = GameObject::AddComponent(centerObject, "UnityEngine", "RectTransform");
		il2cpp_utils::RunMethod(center, parentPropertySet, centerListParent);

		Vector3 pos1, pos2;
		il2cpp_utils::RunMethod(&pos1, pageCentersList[1], anchoredPosition3DGet);
		il2cpp_utils::RunMethod(&pos2, pageCentersList[2], anchoredPosition3DGet);
		float updates = pos2.x - pos1.x;
		//LOG("Page update space %f\n", updates);

		Vector2 anchoredPosition4, offsetMin4, offsetMax4;
		Vector3 anchoredPosition3D4;
		il2cpp_utils::RunMethod(&anchoredPosition4, pageCentersList[4], anchoredPositionGet);
		il2cpp_utils::RunMethod(&anchoredPosition3D4, pageCentersList[4], anchoredPosition3DGet);
		il2cpp_utils::RunMethod(&offsetMin4, pageCentersList[4], offsetMinGet);
		il2cpp_utils::RunMethod(&offsetMax4, pageCentersList[4], offsetMaxGet);

		/*LOG("anchoredPosition4 (%f, %f)\n", anchoredPosition4.x, anchoredPosition4.y);
		LOG("offsetMin4 (%f, %f)\n", offsetMin4.x, offsetMin4.y);
		LOG("offsetMax4 (%f, %f)\n", offsetMax4.x, offsetMax4.y);
		LOG("anchoredPosition3D4 (%f, %f, %f)\n", anchoredPosition3D4.x, anchoredPosition3D4.y, anchoredPosition3D4.z);*/


		Vector2 anchoredPosition{ anchoredPosition4.x + updates, 0 };//anchoredPosition4.x + updates
		Vector3 anchoredPosition3D{ anchoredPosition4.x + updates, 0, 0 };
		Vector2 anchorMin{ 0,0 },
			anchorMax{ 0,0 },
			offsetMin{ offsetMin4.x + updates , 0 },
			offsetMax{ offsetMax4.x + updates, 0 },
			pivot{ 0.5, 0.5 },
			sizeDelta{ -0.16, 0 };


		il2cpp_utils::RunMethod(center, anchoredPositionSet, &anchoredPosition);
		il2cpp_utils::RunMethod(center, anchoredPosition3DSet, &anchoredPosition3D);
		il2cpp_utils::RunMethod(center, anchorMinSet, &anchorMin);
		il2cpp_utils::RunMethod(center, anchorMaxSet, &anchorMax);
		il2cpp_utils::RunMethod(center, offsetMinSet, &offsetMin);
		il2cpp_utils::RunMethod(center, offsetMaxSet, &offsetMax);
		il2cpp_utils::RunMethod(center, pivotSet, &pivot);
		il2cpp_utils::RunMethod(center, sizeDeltaSet, &sizeDelta);

		pageCentersList.Add(center);


		Il2CppObject* songSelPaginatedIndicator = il2cpp_utils::GetFieldValue(songSelectionUIController, "songSelPaginatedIndicator");
		List<Il2CppObject*> pageMarkers(il2cpp_utils::GetFieldValue(songSelPaginatedIndicator, "pageMarkers"));
		Il2CppObject* toInstantiate;
		il2cpp_utils::RunMethod(&toInstantiate, pageMarkers[0], gameObjectGet);
		Il2CppObject* centerTarget = GameObject::Instantiate(toInstantiate);
		Il2CppObject* rectTransform = GameObject::GetComponent(centerTarget, "UnityEngine", "RectTransform");

		Il2CppObject* parentToSet;
		Il2CppObject* parentRectTransform = GameObject::GetComponent(toInstantiate, "UnityEngine", "RectTransform");;
		il2cpp_utils::RunMethod(&parentToSet, parentRectTransform, parentPropertyGet);
		il2cpp_utils::RunMethod(rectTransform, parentPropertySet, parentToSet);

		Vector3 newPosition{ 0, 1.234978f, 4.965f }; //TODO calculate page indicator position dynamically
		il2cpp_utils::RunMethod(rectTransform, positionSet, &newPosition);

		pageMarkers.Add(rectTransform);
	}
}


