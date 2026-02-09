#include "uuid.h"

namespace OB {

    // Quelle: https://gist.github.com/JavaCS3/493cb20c1e4e1bc6f9e8d891077f0174 Thanks You
        #define CHAR2INT(x) (('0' <= x && x <= '9') ? \
            (x - '0') : \
            (('a' <= x && x <= 'f') ? \
                (10 + (x - 'a')) : \
                (('A' <= x && x <= 'F') ? (10 + (x - 'A')) : (0))))

        #define UUID2ARRAY(uuid) { \
            16 * CHAR2INT(uuid[6]) + CHAR2INT(uuid[7]), \
            16 * CHAR2INT(uuid[4]) + CHAR2INT(uuid[5]), \
            16 * CHAR2INT(uuid[2]) + CHAR2INT(uuid[3]), \
            16 * CHAR2INT(uuid[0]) + CHAR2INT(uuid[1]), \
            \
            16 * CHAR2INT(uuid[11]) + CHAR2INT(uuid[12]), \
            16 * CHAR2INT(uuid[9]) + CHAR2INT(uuid[10]), \
            \
            16 * CHAR2INT(uuid[16]) + CHAR2INT(uuid[17]), \
            16 * CHAR2INT(uuid[14]) + CHAR2INT(uuid[15]), \
            \
            16 * CHAR2INT(uuid[19]) + CHAR2INT(uuid[20]), \
            16 * CHAR2INT(uuid[21]) + CHAR2INT(uuid[22]), \
            \
            16 * CHAR2INT(uuid[24]) + CHAR2INT(uuid[25]), \
            16 * CHAR2INT(uuid[26]) + CHAR2INT(uuid[27]), \
            16 * CHAR2INT(uuid[28]) + CHAR2INT(uuid[29]), \
            16 * CHAR2INT(uuid[30]) + CHAR2INT(uuid[31]), \
            16 * CHAR2INT(uuid[32]) + CHAR2INT(uuid[33]), \
            16 * CHAR2INT(uuid[34]) + CHAR2INT(uuid[35]), \
        }

        UUiD::UUiD() noexcept  {
            memset(m_uuid, 0, 16);
        }
 
        UUiD::UUiD (const value_type (&arr)[16]) {
            memcpy_s(m_uuid, 16, arr, 16);
        }
        UUiD::UUiD (const char* stri) { 
            uint8_t _uuidraw[16] = UUID2ARRAY(stri);
            memcpy_s(m_uuid, 16, _uuidraw, 16);
        }

        void UUiD::swap (this_type& other){
            std::swap(m_uuid, other.m_uuid);
        }

        bool UUiD::operator == (const this_type& other) {
            return memcmp(m_uuid, other.m_uuid, 16) == 0;
        }
        bool UUiD::operator != (const this_type& other) {
            return memcmp(m_uuid, other.m_uuid, 16) != 0;
        }

        UUiD::this_type& UUiD::operator = (const this_type& other) {
            memcpy_s(m_uuid, 16, other.m_uuid, 16);
            return *this;
        }
        size_t UUiD::hash() const {
            return m_hUUID ^ (m_lUUID + 0x9e3779b9 + (m_hUUID << 6) + (m_hUUID >> 2));
        }
        std::string UUiD::str() const {
            char str[37] = {};
            unsigned long data1 = *reinterpret_cast<unsigned long*>(m_lUUID);
            unsigned short data2 = *reinterpret_cast<unsigned short*>(m_lUUID + 4);
            unsigned short data3 = *reinterpret_cast<unsigned short*>(m_lUUID + 6);
            sprintf(str, 
            "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
                data1, data2, data3,
                m_lUUID[8], m_lUUID[9], m_lUUID[10], m_lUUID[11], m_lUUID[12], m_lUUID[13], m_lUUID[14], m_lUUID[15]
            );
            return std::string(str);
        }
}