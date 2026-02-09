#include "ObjectLight/ObjectLight.h"
#include <stdint.h>

//#define PrintebleObjectUUID "019c3f3c-dfaa-7e98-818c-590db3522b5b"
#define MyModuleSubVersionUUID "019c3fad-27d9-7fb5-bdd5-a97c5b63833b"
class MyModule : public OB::PrintebleObject {
public:
    using this_type = MyModule;
	using base_type = OB::PrintebleObject;

	MyModule() : base_type(MyModuleSubVersionUUID) {}

	virtual void print(std::ostream stream) {
		stream << "Hallo World UUID: " << uuid().str() << " SubUUID: " << Version_uuid().str() << std::endl; 
	}
};