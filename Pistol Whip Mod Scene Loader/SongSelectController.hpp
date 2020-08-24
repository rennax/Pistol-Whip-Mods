#ifndef SONGSELECTCONTROLLER_HPP
#define SONGSELECTCONTROLLER_HPP
#include "il2cpp_utils.hpp"
#include "json.hpp"
#include <string_view>


using json = nlohmann::json;

void OnEnter();
void OnStay();
void OnExit();
void OnClick();

class SongSelectController
{
public:
	SongSelectController();
	~SongSelectController();	
	//void OnEnter();
	//void OnStay();
	//void OnExit();
	//void OnClick();

private:
	Il2CppObject* Add_CHUIButtonTrigger(Il2CppObject* gameObject);
private:
	Il2CppObject* self; //This is the gameobject
	Il2CppObject* canvas;
	Il2CppObject* songPanel;
	Il2CppObject* songPanelButton;
	//ScrollController scroll;


	std::string_view assetsPath = "Mods/pistol whip mod scene loader assets";
};


#endif