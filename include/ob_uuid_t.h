#pragma once

#include <string>
#include <type_traits>

namespace OB {
    class basic_uuid {
    public:
        using value_type = uint8_t;
        using this_type = basic_uuid;
        using iterator = uint8_t*;
        using const_iterator = const uint8_t*;
        using size_type = size_t;

        basic_uuid() ;

        basic_uuid(const uint8_t(&arr)[16]) noexcept;
        basic_uuid(const char* str) noexcept;

        void        swap (this_type& other) noexcept;
        size_t      hash() const noexcept;
        std::string str() noexcept;

        iterator       begin() noexcept { return m_uuid; }
        const_iterator begin() const noexcept { return m_uuid; }
        iterator       end() noexcept { return m_uuid + 16; }
        const_iterator end() const noexcept { return m_uuid + 16; }
        size_type size() const noexcept { return 16; }

        bool operator == (const this_type& other) noexcept;
        bool operator != (const this_type& other) noexcept;
        this_type& operator = (const this_type& other) noexcept;
    private:
        union  {
            struct {
                uint64_t m_hUUID;
                uint64_t m_lUUID;
            };
            uint8_t m_uuid[16];
        };
    };
    

    inline bool operator < (const basic_uuid& a, const basic_uuid& b) noexcept  {
        return a.hash() < b.hash();
    }
    inline bool operator > (const basic_uuid& a, const basic_uuid& b) noexcept  {
        return a.hash() > b.hash();
    }

    inline void swap(basic_uuid& a, basic_uuid& b) noexcept {
        a.swap(b);
    }

    using uuid_t = basic_uuid;
}

// type traits specializations
namespace std {
    template <>
    struct is_pod<OB::basic_uuid> : true_type {};
}