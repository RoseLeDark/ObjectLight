#pragma once


#include <string>
#include <vector>


namespace OB {
    namespace host {
        
        class object_regestry_entry {
            struct VersionEntry {
                std::string subUUID;
                std::string version;
                std::vector<std::string> changes;
            };
        public:
            bool load_from_file(const std::string& path);
            bool load_from_yaml(YAML::Node root);
        private:
            void add_sub_entry(YAML::detail::iterator_value value);
        private:
            std::string m_strName;
            std::string m_strModule;
            OB::uuid_t m_uuidType;
            std::vector<VersionEntry> m_vecVersions;
        };

        class object_regestry {
        public:
            static bool add_all_from_path(const std::string dir);
            static bool add_from_file(const std::string file);
        private:
            static std::vector<object_regestry_entry> m_vecEntrys;
        };
    }
}

