#pragma once

#include "ob_function.h"
#include <string>
#include <vector>
#include <optional>



namespace OB {
    class Object;
	class ObjectFactory;
	
    // ObjectFactoryEntry create the sub object from the Version
    class ObjectFactoryEntry {
		friend class ObjectFactory;
	public:
		ObjectFactoryEntry(uuid_t version) : m_versionUUID(version) { }
	
		uuid_t sub_version_uuid() const { return m_versionUUID; }

		// Factory functions for creating the Instance
		OB::function<Object*, void*> CreateInstance;
		OB::function<bool, Object*> DestroyInstance;

		constexpr Object* CallCreate(void* userData) const {
			return (CreateInstance != NULL) ? CreateInstance(userData) : nullptr;
		}
		constexpr bool CallDestroyer(Object* obj) const {
			return (DestroyInstance != NULL) ? DestroyInstance(obj) : false;
		}
    private:
		uuid_t m_versionUUID;
    };

   class ObjectFactory {
	public:
		ObjectFactory() = default;
		
		Object* CreateInstance(uuid_t subVersion, void* userData);
		bool ReleaseInstance(Object* instance, uuid_t subVersion);

		bool where(ObjectFactoryEntry* entry, uuid_t version);
		
        void RegisterFactoryEntry(ObjectFactoryEntry* entry) ;
        void UnregisterFactoryEntry(uuid_t subVersion);
	protected:
		Object* CreateInstanceFromEntry(ObjectFactoryEntry* entry, void* userData);
	private:
		std::vector<ObjectFactoryEntry*> m_factoryEntries;
	};
}