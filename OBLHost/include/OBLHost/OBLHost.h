#pragma once

#include <Windows.h>

#include <string>
#include "ObjectLight/ObjectLight.h"

#include <map>
namespace OB {

	namespace host {

		class Factory {
		public:
			static Object* OBLCreateInstance(std::string obPath, 
				uint64_t guid, const int version);

			template<class TIObject>
			static  TIObject* OBLCreateInstanceWithType(std::string obPath,
				uint64_t guid, const int version) {
				return static_cast<TIObject*>(OBLCreateInstance(obPath, guid, version));
			}

			static bool OBLReleaseInstance(Object* instance);

		private:
			static ObjectFactory* GetFectoryFromCache(uint64_t guid);
			static ObjectFactory* GetFectoryFromFile(std::string obPath, uint64_t guid);
		private:
			static std::map<uint64_t, ObjectFactory*> m_factorys;
		};
	}
}