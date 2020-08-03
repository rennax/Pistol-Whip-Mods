#include "typedefs.h"

void to_json(json& j, const Vector3i& vec3)
{
	j = json{ {"x", vec3.x}, {"y", vec3.y}, {"z", vec3.z} };
}

void to_json(json& j, const Vector2i& vec2)
{
	j = json{ {"x", vec2.x}, {"y", vec2.y}};
}

void to_json(json& j, const Quaternion& q)
{
	j = json{ {"x", q.x}, {"y", q.y}, {"z", q.z}, {"w", q.w} };
}


void to_json(json& j, const Vector3& vec3)
{
	j = json{ {"x", vec3.x}, {"y", vec3.y}, {"z", vec3.z} };
}

void to_json(json& j, const Color& c)
{
	j = json{ {"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a} };
}

void to_json(json& j, const Vector2& vec2)
{
	j = json{ {"x", vec2.x}, {"y", vec2.y} };
}