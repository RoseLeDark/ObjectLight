#pragma once

#include "ob_uuid_t.h"
#include <stdint.h>

namespace OB {
	class ObjectFactory;

	class Object {
		friend class ObjectFactory;
	public:
		using type = Object;
        using this_type = Object;

		Object(uuid_t uuid, uuid_t VersionUUID) noexcept
			: m_guid(uuid), m_VersionUUID(VersionUUID), m_refs(0) {
			strcpy_s(m_strName, "Object");
		}
		Object(uuid_t uuid, uuid_t VersionUUID, const char* name)  noexcept
			: m_guid(uuid), m_VersionUUID(VersionUUID), m_refs(0)  {
			strcpy_s(m_strName, name);
		}

		virtual ~Object() = default;

		virtual Object&     add_reference()  noexcept;
		virtual Object&     releases()  noexcept;
		virtual int			reference() const noexcept;
		virtual size_t      hash() const noexcept;

		uuid_t  uuid() const noexcept { return m_guid;  }
		uuid_t  Version_uuid() const noexcept { return m_VersionUUID; }

		virtual bool equel(const Object& other)  noexcept;

        bool operator !=  (const this_type& other) noexcept { return !this->equel(other); }
        bool operator ==  (const this_type& other) noexcept { return this->equel(other); }
        
        this_type& operator ++ () noexcept  { this->add_reference(); return *this; }
        this_type& operator -- () noexcept  { this->releases(); return *this; }

        this_type& operator ++ (int) noexcept  { this->add_reference(); return *this; }
        this_type& operator -- (int) noexcept  { this->releases(); return *this; }
	private:
		uuid_t 	 m_guid;
		uuid_t     m_VersionUUID;
		char     m_strName[16];
		uint32_t m_refs;
	};
}