#include "KoreographyTrackBase.hpp"
#include "List.hpp"
#include "KoreographyEvent.hpp"

using namespace CSharp;

KoreographyTrackBase::KoreographyTrackBase()
{
	Il2CppClass* klass = il2cpp_utils::GetClassFromName("SonicBloom.Koreo", "KoreographyTrackBase");
	self = il2cpp_functions::object_new(klass);
	if (!il2cpp_utils::RunMethod(self, ".ctor"))
		LOG("WARNING: Failed to construct KoreographyTrackBase\n");

}

KoreographyTrackBase::KoreographyTrackBase(Il2CppObject* obj) : self(obj)
{
}

KoreographyTrackBase::~KoreographyTrackBase()
{
}

Il2CppObject* KoreographyTrackBase::Load(json j)
{
	il2cpp_utils::SetFieldValue(self, "mEventID", il2cpp_utils::createcsstr(j["mEventID"]));

	List<Il2CppObject*> mEventList(il2cpp_utils::GetFieldValue(self, "mEventList"));
	for (auto e : j["mEventList"])
	{
		KoreographyEvent mEvent;
		mEventList.Add(mEvent.Load(e));
	}

	return self;
}

json KoreographyTrackBase::Dump()
{
	json j;

	Il2CppString* eventID = nullptr;
	il2cpp_utils::GetFieldValue(&eventID, self, "mEventID");
	if (eventID != nullptr)
		mEventID = to_utf8(csstrtostr(eventID));
	j["mEventID"] = mEventID;

	List<Il2CppObject*> eventList(il2cpp_utils::GetFieldValue(self, "mEventList"));
	for (size_t i = 0; i < eventList.Count(); i++)
	{
		KoreographyEvent event(eventList[i]);
		j["mEventList"].push_back(event.Dump());
	}

	List<Il2CppObject*> inRange(il2cpp_utils::GetFieldValue(self, "eventsInRange"));
	for (size_t i = 0; i < inRange.Count(); i++)
	{
		KoreographyEvent item(inRange[i]);
		j["eventsInRange"].push_back(item.Dump());
	}

	//TODO update list to support Il2CppString*
	//List<Il2CppString*> serializedPayloadTypes(il2cpp_utils::GetFieldValue(self, "_SerializedPayloadTypes"));
	//for (size_t i = 0; i < inRange.Count(); i++)
	//{
	//	Il2CppString* csstr = serializedPayloadTypes[i];
	//	
	//	if (csstr != nullptr)
	//	{
	//		j["_SerializedPayloadTypes"].push_back(to_utf8(csstrtostr(csstr)));
	//	}

	//	
	//}

	return j;
}
