#ifndef IPAYLOAD_HPP
#define IPAYLOAD_HPP
//All classes in this file, implements the IPayload interface

#include "il2cpp_utils.hpp"
#include "json.hpp"

using json = nlohmann::json;


class AssetPayload
{
public:
	AssetPayload() {}
	AssetPayload(Il2CppObject* obj) : self(obj) {}
	~AssetPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "Asset";
		
		il2cpp_utils::GetFieldValue(mAssetVal, self, "mAssetVal");
		
		Il2CppString* str = nullptr;
		std::string assetName;
		il2cpp_utils::RunMethod(str, mAssetVal, "get_name");
		if (str != nullptr)
			assetName = to_utf8(csstrtostr(str));

		j["assetName"] = assetName;
		return j;
	}
private:
	Il2CppObject* self;
	Il2CppObject* mAssetVal;
};

class ColorPayload
{
public:
	ColorPayload(Il2CppObject* obj) : self(obj) {}
	~ColorPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "color";

		il2cpp_utils::GetFieldValue(&mColorVal, self, "mColorVal");

		j["colorVal"]["r"] = mColorVal.r;
		j["colorVal"]["g"] = mColorVal.g;
		j["colorVal"]["b"] = mColorVal.b;
		j["colorVal"]["a"] = mColorVal.a;
		return j;
	}
private:
	Il2CppObject* self = nullptr;
	Color mColorVal = { 0,0,0,0 };
};

class CurvePayload {
public:
	CurvePayload(Il2CppObject* obj) : self(obj) {}
	~CurvePayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "curve";
		return j;
	}
private:
	Il2CppObject* self = nullptr;
};


class FloatPayload
{
public:
	FloatPayload(Il2CppObject* obj) : self(obj) {}
	~FloatPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "float";
		il2cpp_utils::GetFieldValue(&mFloatVal, self, "mFloatVal");
		j["mFloatVal"] = mFloatVal;
		return j;
	}
private:
	Il2CppObject* self = nullptr;
	float mFloatVal = 0;
};


class GradientPayload {
public:
	GradientPayload(Il2CppObject* obj) : self(obj) {}
	~GradientPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "gradient";
		return j;
	}
private:
	Il2CppObject* self = nullptr;
};

class IntPayload
{
public:
	IntPayload(Il2CppObject* obj) : self(obj) {}
	~IntPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "int";
		il2cpp_utils::GetFieldValue(&mIntVal, self, "mIntVal");
		j["mIntVal"] = mIntVal;
		return j;
	}
private:
	Il2CppObject* self = nullptr;
	int64_t mIntVal = 0;
};

class SpectrumPayload {
public:
	SpectrumPayload(Il2CppObject* obj) : self(obj) {}
	~SpectrumPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "spectrum";
		return j;
	}
private:
	Il2CppObject* self = nullptr;
};


class TextPayload {
public:
	TextPayload(Il2CppObject* obj) : self(obj) {}
	~TextPayload() {}
	json Dump() {
		json j;
		j["payloadType"] = "text";

		std::string text;
		Il2CppString* str = nullptr;
		il2cpp_utils::GetFieldValue(&str, self, "mTextVal");

		if (str != nullptr)
			text = to_utf8(csstrtostr(str));

		j["mTextVal"] = text;

		return j;
	}
private:
	Il2CppObject* self = nullptr;
};

#endif // !IPAYLOAD_HPP
