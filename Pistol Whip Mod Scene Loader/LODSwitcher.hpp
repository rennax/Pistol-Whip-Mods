#ifndef LODSWITCHER_HPP
#define LODSWITCHER_HPP

#include "il2cpp_utils.hpp"
#include "json.hpp"
#include <string>

using json = nlohmann::json;

class LODSwitcher
{
public:
	LODSwitcher();
	~LODSwitcher();
	static json Dump(Il2CppObject* obj);
private:

};

LODSwitcher::LODSwitcher()
{
}

LODSwitcher::~LODSwitcher()
{
}

json LODSwitcher::Dump(Il2CppObject* obj)
{
	bool isEnemy;
	il2cpp_utils::GetFieldValue(&isEnemy, obj, "isEnemy");
	
	int fixedLODLevel;
	il2cpp_utils::GetFieldValue(&fixedLODLevel, obj, "fixedLODLevel");

	int lodLevel;
	il2cpp_utils::GetFieldValue(&lodLevel, obj, "lodLevel");

	int maxLOD;
	il2cpp_utils::GetFieldValue(&maxLOD, obj, "maxLOD");

	int modulo;
	il2cpp_utils::GetFieldValue(&modulo, obj, "modulo");

	std::stringstream ss;
	ss << "isEnemy: " << isEnemy << " lodLevel: " << lodLevel << " maxLOD: " << maxLOD;
	LOG("%s\n", ss.str().c_str());


	return json();
}

#endif // !LODSWITCHER_HPP
