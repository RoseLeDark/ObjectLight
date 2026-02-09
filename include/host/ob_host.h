#pragma once

#include <string>
#include "ob_object_light.h"
#include <map>

namespace OB {

	namespace host {

		class Factory {
		public:
			static Object* OBLCreateInstance(std::string obPath, 
				const uuid_t guid, const uuid_t version, void* userdata = nullptr);

			template<class TIObject>
			static  TIObject* OBLCreateInstanceWithType(std::string obPath,
				const uuid_t guid, const uuid_t version, void* userdata = nullptr) {
				return static_cast<TIObject*>(OBLCreateInstance(obPath, guid, version, userdata));
			}

			static bool OBLReleaseInstance(Object* instance);

		private:
			static ObjectFactory* GetFectoryFromCache(const uuid_t guid);
			static ObjectFactory* GetFectoryFromFile(std::string obPath, const uuid_t guid);
		private:
			static std::map<uuid_t, ObjectFactory*> m_factorys;
		};
	}
}