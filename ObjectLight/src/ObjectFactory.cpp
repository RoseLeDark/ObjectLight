#include "ObjectFactory.h"
#include "Object.h"
#include <vector>

namespace OB {
    Object* ObjectFactory::CreateInstance(uuid version) {
        Object* _ret = nullptr;

        for (const auto entry : m_factoryEntries) {
            if (entry->sub_version_uuid() == version) {
                _ret = CreateInstanceFromEntry(entry);
            }
        }

        return _ret; // No matching version found
    }

    bool ObjectFactory::ReleaseInstance(Object* instance, uuid version) {
        bool _ret = false;

        for (const auto entry : m_factoryEntries) {
            if (entry->sub_version_uuid() == version) {
                _ret = entry->CallDestroyer(instance);
            }
        }
        return _ret;
    }

    void ObjectFactory::RegisterFactoryEntry(ObjectFactoryEntry* entry) {
        m_factoryEntries.push_back(entry);
    }

    bool ObjectFactory::where(ObjectFactoryEntry* entry, int version) {
        return entry->sub_version_uuid() == version;
    }
    void ObjectFactory::UnregisterFactoryEntry(uuid version) {
        auto erased = std::erase_if(m_factoryEntries,
         [version](ObjectFactoryEntry* x) { uuid v = x->sub_version_uuid();  return v == version; });
    }
    Object* ObjectFactory::CreateInstanceFromEntry(ObjectFactoryEntry* entry) {
        Object* obj = nullptr;
        entry->CallCreate(obj);
        return obj;
    }
}