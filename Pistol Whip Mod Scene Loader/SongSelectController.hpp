#ifndef SONGSELECTCONTROLLER_HPP
#define SONGSELECTCONTROLLER_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include <string_view>


using json = nlohmann::json;

class SongSelectController
{
public:
	SongSelectController();
	~SongSelectController();	
	static void OnEnter(void* self);
	static void OnStay(void* self);
	static void OnExit(void* self);
	static void OnClick(void* self);
	static void NextNext();
	static void PreviousSong();
	void SetText(std::string text);
private:
	Il2CppObject* Add_CHUIButtonTrigger(Il2CppObject* gameObject);
private:
	Il2CppObject* self; //This is the gameobject
	Il2CppObject* canvas;
	Il2CppObject* songPanel;
	Il2CppObject* songPanelButton;
	//ScrollController scroll;
	Il2CppObject* tmpProText;

	std::string_view assetsPath = "Mods/pistol whip mod scene loader assets";
};


#endif