#include "include/OBL/Object.h"
#include <string.h>

namespace OB {
    Object::Object(uint64_t guid, uint16_t iVersion, const char* name)
        : m_guid(guid), m_iVersion(iVersion), m_refs(0) { 
        strcpy_s(m_strName, name); 
    }

    Object&     Object::add_reference() { 
        m_refs--; 
        return *this;  
    }
	Object&     Object::releases() { 
        m_refs--; 
        return *this; 
    }
	int			Object::reference() { 
        return m_refs; 
    }

    bool Object::equel(const Object& other) {
        if (m_guid != other.m_guid) return false;
        if (strcmp(m_strName, other.m_strName) == 0) return false;
        return m_iVersion == other.m_iVersion;
    }

}