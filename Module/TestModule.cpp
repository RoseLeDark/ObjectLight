#include "ob_object_light.h"
#include "TestModule.h"


class MyModuleObjectEntry1 : public OB::ObjectFactoryEntry{
public:
	MyModuleObjectEntry1() : ObjectFactoryEntry(TestModuleOneUUID) {
	
		CreateInstance = TestModuleOne::CreateInstance;
		DestroyInstance = TestModuleOne::DestroyInstance;
	}
};

class MyModuleObjectEntry2 : public OB::ObjectFactoryEntry {
public:
	MyModuleObjectEntry2() : ObjectFactoryEntry(TestModuleTwoUUID) {
		CreateInstance = TestModuleTwo::CreateInstance;
		DestroyInstance = TestModuleTwo::DestroyInstance;
	}
};

extern "C" OB::ObjectFactory* OBLGetFactory(const OB::uuid_t& id) {
	OB::ObjectFactory* factory = new OB::ObjectFactory();

	factory->RegisterFactoryEntry(new MyModuleObjectEntry1());
	factory->RegisterFactoryEntry(new MyModuleObjectEntry2());

	return factory;
}