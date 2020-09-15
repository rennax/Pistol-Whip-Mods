#include "Sprite.hpp"
#include <fstream>

Sprite::Sprite(fs::path path, json imgConfig) : imgPath(path)
{
	width = imgConfig["width"];
	height = imgConfig["height"];
	LoadSprite();
}

Sprite::Sprite(fs::path path, int32_t _width, int32_t _height): imgPath(path), width(_width), height(_height)
{
	LoadSprite();
}

Sprite::~Sprite()
{}

Il2CppObject* Sprite::GetObj()
{
	return self;
}


//TODO extract size from texture, so we dont need to pass it ourself
void Sprite::LoadTexture2D()
{
	static auto texture2DClass = il2cpp_utils::GetClassFromName("UnityEngine", "Texture2D");
	static auto byteClass = il2cpp_utils::GetClassFromName("System", "Byte");
	static auto imgConversionClass = il2cpp_utils::GetClassFromName("UnityEngine", "ImageConversion");


	texture = il2cpp_functions::object_new(texture2DClass);
	il2cpp_utils::RunMethod(texture, ".ctor", &width, &height);

	//Open image file and get size
	std::ifstream f(imgPath, std::ios::binary | std::ios::ate);
	size_t size = f.tellg();
	f.seekg(0);

	//TODO optimize/sanitize this section with copying data
	char* data = new char[size];//yikes
	f.read(data, size); //Tried reading directly into a Array<uint8_t>*->values but that didn't work
	Il2CppArray* buff = il2cpp_functions::array_new(byteClass, size);
	
	for (size_t i = 0; i < size; i++)
	{
		il2cpp_array_set(buff, uint8_t, i, data[i]);
	}
	delete[] data;

	bool markNonReadable = false;
	if (!il2cpp_utils::RunMethod(imgConversionClass, "LoadImage", texture, buff, &markNonReadable))
		LOG("Failed to call function ImageConversion.LoadImage\n");
}

void Sprite::LoadSprite()
{
	static auto spriteClass = il2cpp_utils::GetClassFromName("UnityEngine", "Sprite");
	LoadTexture2D();
	Vector2 pivot{ 0.5, 0.5 };
	Rect rect{ 0, 0, width, height };
	float pixelsPerUnit = 100;
	if (!il2cpp_utils::RunMethod(&self, spriteClass, "Create", texture, &rect, &pivot, &pixelsPerUnit))
		LOG("WARNING: Sprite: Failed to create a sprite with Create\n");
}
