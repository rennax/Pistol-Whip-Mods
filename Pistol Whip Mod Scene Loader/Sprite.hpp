#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "json.hpp"
#include "il2cpp_utils.hpp"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

struct Rect {
	float m_XMin; 
	float m_YMin; 
	float m_Width;
	float m_Height;
};

class Sprite
{
public:
	Sprite(fs::path path, json imgConfig);
	Sprite(fs::path path, int32_t _width, int32_t _height);
	~Sprite();
	Il2CppObject* GetObj();
private:
	void LoadTexture2D();
	void LoadSprite();
private:
	Il2CppObject* self; //Sprite
	Il2CppObject* texture; //Texture2D
	int32_t width;
	int32_t height;
	fs::path imgPath;
};


#endif // !SPRITE_HPP

