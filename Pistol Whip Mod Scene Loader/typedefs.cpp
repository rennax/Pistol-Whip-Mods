#include "typedefs.h"

void to_json(json& j, const Vector3i& vec3)
{
	j = json{ {"x", vec3.x}, {"y", vec3.y}, {"z", vec3.z} };
}
void from_json(const json& j, Vector3i& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
	j.at("z").get_to(v.z);
}

void to_json(json& j, const Vector2i& vec2)
{
	j = json{ {"x", vec2.x}, {"y", vec2.y}};
}
void from_json(const json& j, Vector2i& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}

void to_json(json& j, const Quaternion& q)
{
	j = json{ {"x", q.x}, {"y", q.y}, {"z", q.z}, {"w", q.w} };
}
void from_json(const json& j, Quaternion& q)
{
	j.at("x").get_to(q.x);
	j.at("y").get_to(q.y);
	j.at("z").get_to(q.z);
	j.at("w").get_to(q.w);
}

void to_json(json& j, const Vector3& vec3)
{
	j = json{ {"x", vec3.x}, {"y", vec3.y}, {"z", vec3.z} };
}
void from_json(const json& j, Vector3& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
	j.at("z").get_to(v.z);
}

void to_json(json& j, const Vector2& vec2)
{
	j = json{ {"x", vec2.x}, {"y", vec2.y} };
}
void from_json(const json& j, Vector2& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}

void to_json(json& j, const Color& c)
{
	j = json{ {"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a} };
}
void from_json(const json& j, Color& c)
{
	j.at("r").get_to(c.r);
	j.at("g").get_to(c.b);
	j.at("b").get_to(c.g);
	j.at("a").get_to(c.a);
}

