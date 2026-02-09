#include <OBL/OBLight.h>
#include "include/Module/TestModule.h"


static bool MyObjectCreateInstance1(OB::Object* obj) {
		obj = new MyModule(1);
		return 1;
}
static bool MyObjectDestroyInstance1(OB::Object* obj) {
	if (obj != NULL) {
		if (obj->reference() == 0) {
			delete obj;
			obj = NULL;
		}
	}
	return 0;
}

class MyModuleObjectEntry1 : public OB::ObjectFactoryEntry{
public:
	MyModuleObjectEntry1() : ObjectFactoryEntry(1) {
	
		CreateInstance = MyObjectCreateInstance1;
		DestroyInstance = MyObjectDestroyInstance1;
	}
};

static int MyObjectCreateInstance2(OB::Object* obj) {
	obj = new MyModule(2);
	return 1;
}

class MyModuleObjectEntry2 : public OB::ObjectFactoryEntry {
public:
	MyModuleObjectEntry2() : ObjectFactoryEntry(2) {

		CreateInstance = MyObjectCreateInstance2;
		DestroyInstance = MyObjectDestroyInstance1;
	}
};

extern "C" OB::ObjectFactory* OBLGetFactory(const OB::uuid& id) {
	OB::ObjectFactory* factory = new OB::ObjectFactory();

	factory->RegisterFactoryEntry(new MyModuleObjectEntry1());
	factory->RegisterFactoryEntry(new MyModuleObjectEntry2());

	return factory;
}