#include <yaml-cpp/yaml.h>

#include "ob_uuid_t.h"
#include "host/ob_regestry.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>

namespace OB {
    namespace host {
        bool object_regestry_entry::load_from_file(const std::string& path) {
            return load_from_yaml(YAML::LoadFile(path));
        }

        bool object_regestry_entry::load_from_yaml(YAML::Node root) {

            try {
                m_strName = root["Name"].as<std::string>();
                m_strModule = root["module"].as<std::string>();

                std::string uuid = root["typeUUID"].as<std::string>();

                m_uuidType = OB::uuid_t(uuid.c_str());

                for (YAML::detail::iterator_value v : root["versions"]) {
                    add_sub_entry(v);
                }
            }
            catch(std::exception ) {
                return false;
            }
            return true;
        }
        void object_regestry_entry::add_sub_entry(YAML::detail::iterator_value value) {
            VersionEntry ve;
            ve.subUUID = value["subUUID"].as<std::string>();
            ve.version = value["version"].as<std::string>();
            ve.changes = value["changes"].as<std::vector<std::string>>();
            m_vecVersions.push_back(ve);
        }

        std::vector<object_regestry_entry> object_regestry::m_vecEntrys;

        bool object_regestry::add_all_from_path(const std::string path) {
            struct stat sb;

            for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {

                std::filesystem::path outfilename = entry.path();

                // Testing whether the path points to a
                // non-directory or not If it does, displays path
                if (entry.is_regular_file() && outfilename.extension().string() == ".oreg") {
                     add_from_file(outfilename.string());
                }
            }
        }
        bool object_regestry::add_from_file(const std::string file) {
            object_regestry_entry entry ;

            entry.load_from_file(file);
            m_vecEntrys.push_back(entry);
        }
    }
}