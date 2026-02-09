#include "OBLHost/OBLHost.h"
#include "ObjectLight/ObjectLight.h"
#include "ObjectLight/Object.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <libloaderapi.h>
#endif

#include <map>


namespace OB {
	std::map<uint64_t, ObjectFactory*> host::Factory::m_factorys;

	
	Object* host::Factory::OBLCreateInstance(std::string obPath,
		uint64_t guid, const int version) {
		Object* _ret = nullptr;
		

		ObjectFactory* factory = GetFectoryFromCache(guid);
		if(factory == nullptr) factory = GetFectoryFromFile(obPath, guid);

		if (factory) {
			_ret = factory->CreateInstance(version);
			if (_ret) _ret->add_reference();
		}
		return _ret;
	}
	ObjectFactory* host::Factory::GetFectoryFromCache(uint64_t guid) {
		auto find = m_factorys.find(guid);
		if (find != m_factorys.end())
			return find->second;
		return nullptr;
	}

	bool host::Factory::OBLReleaseInstance(Object* instance) {
		auto factory = GetFectoryFromCache(instance->guid());

		if (factory == NULL) return false;

		instance--;

		if (instance->reference() <= 0) {
			factory->ReleaseInstance(instance, instance->version() );
		}
		return true;
	}
	ObjectFactory* host::Factory::GetFectoryFromFile(std::string obPath, uint64_t guid) {
		LPOBLGetFactory getFactoryProc = nullptr;
		OB::ObjectFactory* factory = nullptr;

#if defined(_WIN32) || defined(_WIN64)
		HMODULE hModule = LoadLibraryA(obPath.c_str());
		if (!hModule) return nullptr;
		getFactoryProc = (LPOBLGetFactory)GetProcAddress(hModule, "OBLGetFactory");
#endif
		if (getFactoryProc) {
			factory = getFactoryProc(guid);
			m_factorys.insert_or_assign(guid, factory);
		}
#if defined(_WIN32) || defined(_WIN64)
		FreeLibrary(hModule);
#endif
		return factory;
	}
}