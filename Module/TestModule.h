#include "ob_object_light.h"
#include "ob_objects.h"
#include "ob_uuid_t.h"

#include <stdint.h>
#include <iostream>

//#define PrintebleObjectUUID "019c3f3c-dfaa-7e98-818c-590db3522b5b"
#define TestModuleOneUUID "019c3fad-27d9-7fb5-bdd5-a97c5b63833b" // Version 1
class TestModuleOne : public OB::PrintebleObject {
public:
    using this_type = TestModuleOne;
	using base_type = OB::PrintebleObject;

	TestModuleOne() : base_type(TestModuleOneUUID) {}

	virtual void print(std::ostream stream) {
		stream << "Hallo World 1 UUID: " << uuid().str() << " SubUUID: " << Version_uuid().str() << std::endl; 
	}
	static OB::Object* CreateInstance(void* obj) {
		return new TestModuleOne();
	}
	static bool DestroyInstance(OB::Object* obj) {
		if (obj != nullptr) {
			if (obj->reference() == 0) {
				delete obj;
				obj = NULL;
			}
		}
		return true;
	}
};

//#define PrintebleObjectUUID "019c3f3c-dfaa-7e98-818c-590db3522b5b"
#define TestModuleTwoUUID "019c4053-66b9-7716-9ad6-7e5a77e15e26" // Version 2
class TestModuleTwo : public OB::PrintebleObject {
public:
	using this_type = TestModuleTwo;
	using base_type = OB::PrintebleObject;

	TestModuleTwo() : base_type(TestModuleTwoUUID) {}

	virtual void print(std::ostream stream) {
		stream << "Hallo World 2 UUID: " << uuid().str() << " SubUUID: " << Version_uuid().str() << std::endl;
	}

	static OB::Object* CreateInstance(void* obj) {
		return new TestModuleTwo();
	}
	static bool DestroyInstance(OB::Object* obj) {
		if (obj != nullptr) {
			if (obj->reference() == 0) {
				delete obj;
				obj = NULL;
			}
		}
		return true;
	}
};