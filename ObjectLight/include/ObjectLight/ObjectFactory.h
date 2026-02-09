#pragma once

#include "Common.h"
#include "Function.h"
#include <string>
#include <vector>
#include <optional>



namespace OB {
    class Object;
	class ObjectFactory;
	
    // ObjectFactoryEntry create the sub object from the Version
    class OBL_API ObjectFactoryEntry {
		friend class ObjectFactory;
	public:
		ObjectFactoryEntry(uuid version) : m_versionUUID(version) { }
	
		uuid sub_version_uuid() const { return m_versionUUID; }

		// Factory functions for creating the Instance
		OB::function<bool, Object*> CreateInstance;
		OB::function<bool, Object*> DestroyInstance;

		constexpr bool CallCreate(Object* obj) const {
			return (CreateInstance != NULL) ? CreateInstance(obj) : false;
		}
		constexpr bool CallDestroyer(Object* obj) const {
			return (DestroyInstance != NULL) ? DestroyInstance(obj) : false;
		}
    private:
		uuid m_versionUUID;
    };

    class OBL_API ObjectFactory {
	public:
		ObjectFactory() = default;
		
		Object* CreateInstance(uuid subVersion);
		bool ReleaseInstance(Object* instance, uuid subVersion);

		

		bool where(ObjectFactoryEntry* entry, int version);
		
        void RegisterFactoryEntry(ObjectFactoryEntry* entry) ;
        void UnregisterFactoryEntry(uuid subVersion);	
	protected:
		Object* CreateInstanceFromEntry(ObjectFactoryEntry* entry);
	private:
		std::vector<ObjectFactoryEntry*> m_factoryEntries;
	};
}