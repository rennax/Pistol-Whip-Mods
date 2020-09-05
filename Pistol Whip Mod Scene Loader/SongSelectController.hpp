#ifndef SONGSELECTCONTROLLER_HPP
#define SONGSELECTCONTROLLER_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include <string_view>
#include "LevelData.hpp"

using json = nlohmann::json;

class SongSelectController
{
public:
	static SongSelectController* get_Instance();
	static void OnEnter(SongSelectController* self);
	static void OnStay(SongSelectController* self);
	static void OnExit(SongSelectController* self);
	static void OnClick();
	static void NextNext();
	static void PreviousSong();
	void SetText(std::string text);

private:
	Il2CppObject* Add_CHUIButtonTrigger(Il2CppObject* gameObject);
	void CreateLevelData(); //Just for test
	Il2CppObject* GetGameMap(Difficulty difficulty);
	SongSelectController();
	~SongSelectController();
private:
	static SongSelectController* _instance;
	Il2CppObject* self; //This is the gameobject
	Il2CppObject* gameManager;
	Il2CppObject* canvas;
	Il2CppObject* songPanel;
	Il2CppObject* songPanelButton;
	//ScrollController scroll;
	Il2CppObject* tmpProText;
	
	//TODO create a level database with album art. This is just temp test code
	Il2CppObject* levelData;
	LevelData data;

	std::string_view assetsPath = "Mods/pistol whip mod scene loader assets";
};


#endif