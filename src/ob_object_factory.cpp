#include "ob_object.h"
#include "ob_object_factory.h"
#include <vector>

namespace OB {
    Object* ObjectFactory::CreateInstance(uuid_t version, void* userData) {
        Object* _ret = nullptr;

        for (const auto entry : m_factoryEntries) {
            if (entry->sub_version_uuid() == version) {
                _ret = CreateInstanceFromEntry(entry, userData);
                break;
            }
        }

        return _ret; // No matching version found
    }

    bool ObjectFactory::ReleaseInstance(Object* instance, uuid_t version) {
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

    bool ObjectFactory::where(ObjectFactoryEntry* entry, OB::uuid_t version) {
        return entry->sub_version_uuid() == version;
    }
    void ObjectFactory::UnregisterFactoryEntry(uuid_t version) {
        auto erased = std::erase_if(m_factoryEntries,
         [version](ObjectFactoryEntry* x) { uuid_t v = x->sub_version_uuid();  return v == version; });
    }
    Object* ObjectFactory::CreateInstanceFromEntry(ObjectFactoryEntry* entry, void* userData) {
        return entry->CallCreate(userData);
    }
}