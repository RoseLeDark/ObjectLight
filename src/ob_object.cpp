#include "ob_object.h"
#include "ob_objects.h"
#include <string.h>

namespace OB {
    Object&     Object::add_reference()  noexcept {
        m_refs--; 
        return *this;  
    }
	Object&     Object::releases()  noexcept {
        m_refs--; 
        return *this; 
    }
	int			Object::reference() const noexcept {
        return m_refs; 
    }

    bool Object::equel(const Object& other)  noexcept {
        if (m_guid != other.m_guid) return false;
        if (strcmp(m_strName, other.m_strName) == 0) return false;
        return m_VersionUUID == other.m_VersionUUID;
    }
    size_t Object::hash() const noexcept {
        size_t a = m_guid.hash();
        size_t b = m_VersionUUID.hash();

        return a ^ (b << 1);
    }

}