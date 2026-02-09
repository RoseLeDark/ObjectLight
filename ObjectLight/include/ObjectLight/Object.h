#pragma once

#include "Common.h"
#include "uuid.h"
#include <stdint.h>

namespace OB {
	class ObjectFactory;

	class OBL_API Object {
		friend class ObjectFactory;
	public:
		using type = Object;
        using this_type = Object;

        Object(uuid guid) : this_type(guid, 1, "Object") { }
        Object(uuid guid, uuid VersionUUID) : this_type(guid, VersionUUID, "Object") { }
		Object(uuid guid, uuid VersionUUID, const char* name);

		virtual ~Object() = default;

		virtual Object&     add_reference();
		virtual Object&     releases();
		virtual int			reference();

		uuid  uuid() const	{ return m_guid;  }
		uuid  Version_uuid() const { return m_VersionUUID; }

		virtual bool equel(const Object& other);

        bool operator !=  (const this_type& other) { return !this->equel(other); }
        bool operator ==  (const this_type& other) { return this->equel(other); }
        
        this_type& operator ++ () { this->add_reference(); return *this; }
        this_type& operator -- () { this->releases(); return *this; }

        this_type& operator ++ (int) { this->add_reference(); return *this; }
        this_type& operator -- (int) { this->releases(); return *this; }
	private:
		uuid 	 m_guid;
		uuid     m_VersionUUID;
		char     m_strName[16];
		uint32_t m_refs;
	};
}