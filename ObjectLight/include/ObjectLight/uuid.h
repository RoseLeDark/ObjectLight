#pragma once

#include <string>


#include "Common.h"

namespace OB {
    class OBL_API UUiD {
    public:
        using value_type = uint8_t;
        using this_type = UUiD;

        UUiD() noexcept; // NILL

        explicit UUiD (const value_type (&)[16]);
        explicit UUiD(const char* str);

        void        swap (this_type& other);
        size_t      hash() const;
        std::string str() const;

        bool operator == (const this_type& other);
        bool operator != (const this_type& other);
        this_type& operator = (const this_type& other);
    private:
        union  {
            struct {
                uint64_t m_hUUID;
                uint64_t m_lUUID;
            };
            value_type m_uuid[16];
        };
    };
    using uuid = UUiD;
}