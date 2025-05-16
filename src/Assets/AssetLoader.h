//
// Created by Kurt Slagle on 5/15/25.
//

#pragma once

#include <cereal/archives/json.hpp>
#include <fstream>
#include <cereal/cereal.hpp>
#include <string>

/*
*    cereal::JSONInputArchive archive(file);
archive(cereal::make_nvp("waveData", m_config));
*/


    template<class T>
    bool LoadJSONAsset(const std::string &path,
                       const std::string &nvp,
                       T &asset) {
        std::ifstream file(path);
        if (!file) {
            return false;
        }

        try {
            cereal::JSONInputArchive archive(file);
            archive(cereal::make_nvp(nvp.c_str(), asset));
        } catch (...) {
            return false;
        }
        return true;
    }

