#include "ob_uuid_t.h"
#include <cstdint>
#include <string>

namespace OB {

    // Quelle: https://gist.github.com/JavaCS3/493cb20c1e4e1bc6f9e8d891077f0174 Thanks You
        #define CHAR2INT(x) (('0' <= x && x <= '9') ? \
            (x - '0') : \
            (('a' <= x && x <= 'f') ? \
                (10 + (x - 'a')) : \
                (('A' <= x && x <= 'F') ? (10 + (x - 'A')) : (0))))

        #define UUID2ARRAY(str) { \
            16 * CHAR2INT(str[6]) + CHAR2INT(str[7]), \
            16 * CHAR2INT(str[4]) + CHAR2INT(str[5]), \
            16 * CHAR2INT(str[2]) + CHAR2INT(str[3]), \
            16 * CHAR2INT(str[0]) + CHAR2INT(str[1]), \
            \
            16 * CHAR2INT(str[11]) + CHAR2INT(str[12]), \
            16 * CHAR2INT(str[9]) + CHAR2INT(str[10]), \
            \
            16 * CHAR2INT(str[16]) + CHAR2INT(str[17]), \
            16 * CHAR2INT(str[14]) + CHAR2INT(str[15]), \
            \
            16 * CHAR2INT(str[19]) + CHAR2INT(str[20]), \
            16 * CHAR2INT(str[21]) + CHAR2INT(str[22]), \
            \
            16 * CHAR2INT(str[24]) + CHAR2INT(str[25]), \
            16 * CHAR2INT(str[26]) + CHAR2INT(str[27]), \
            16 * CHAR2INT(str[28]) + CHAR2INT(str[29]), \
            16 * CHAR2INT(str[30]) + CHAR2INT(str[31]), \
            16 * CHAR2INT(str[32]) + CHAR2INT(str[33]), \
            16 * CHAR2INT(str[34]) + CHAR2INT(str[35]), \
        }

    basic_uuid::basic_uuid()   {
        memset(m_uuid, 0, 16);
    }
 
    basic_uuid::basic_uuid(const uint8_t (&arr)[16]) noexcept {
        memcpy_s(m_uuid, 16, arr, 16);
    }
    basic_uuid::basic_uuid(const char* stri) noexcept  {
        int _uuidraw[16] = UUID2ARRAY(stri);
        memcpy_s(m_uuid, 16, _uuidraw, 16);
    }

    void basic_uuid::swap (this_type& other) noexcept  {
        std::swap(m_uuid, other.m_uuid);
    }

    bool basic_uuid::operator == (const basic_uuid& other) noexcept  {
        return memcmp(m_uuid, other.m_uuid, 16) == 0;
    }
    bool basic_uuid::operator != (const basic_uuid& other) noexcept  {
        return memcmp(m_uuid, other.m_uuid, 16) != 0;
    }

    basic_uuid::this_type& basic_uuid::operator = (const basic_uuid& other) noexcept {
        memcpy_s(m_uuid, 16, other.m_uuid, 16);
        return *this;
    }
    size_t basic_uuid::hash() const noexcept  {
        return m_hUUID ^ (m_lUUID + 0x9e3779b9 + (m_hUUID << 6) + (m_hUUID >> 2));
    }
    std::string basic_uuid::str() noexcept  {
        char str[37] = {};
        unsigned long data1 = *reinterpret_cast<unsigned long*>(m_uuid);
        unsigned short data2 = *reinterpret_cast<unsigned short*>(m_uuid + 4);
        unsigned short data3 = *reinterpret_cast<unsigned short*>(m_uuid + 6);
        sprintf(str, 
        "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
            data1, data2, data3,
            m_uuid[8], m_uuid[9], m_uuid[10], m_uuid[11], m_uuid[12], m_uuid[13], m_uuid[14], m_uuid[15]
        );
        return std::string(str);
    }
}