//
// Created by Kurt Slagle on 12/31/24.
//

#include "IniConfig.h"
#include <fmt/format.h>
#include <fmt/ostream.h>

IniConfig::IniConfig(const std::string &filename) {
    Read(filename);
}

IniConfig::IniConfig() = default;

void IniConfig::Read(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile)
    {
        return;
    }

    std::string currentLine;
    std::string currentSection;
    std::string key, value;

    while (std::getline(infile, currentLine))
    {
        if (currentLine.empty() || currentLine[0] == ';') continue;
        if (currentLine[0] == '[' && currentLine.back() == ']')
        {
            currentSection = currentLine.substr(1, currentLine.size() - 2);
        }
        else
        {
            const auto pos = currentLine.find("=");
            if (pos != std::string::npos)
            {
                key                           = currentLine.substr(0, pos);
                value                         = currentLine.substr(pos + 1);
                m_values[currentSection][key] = value;
            }
        }
    }
}

void IniConfig::Print(std::ostream &out) const {
    for (const auto [sectionName, sectionEntries] : m_values)
    {
        fmt::print(out, "[{}]\n", sectionName);
        // out << "[" << sectionName << "]" << "\n";
        for (const auto [key, value] : sectionEntries)
        {
            fmt::print(out, "\t{}={}\n", key, value);
            // out << "\t" << key << " = " << value << "\n";
        }
    }
    fmt::println("");
}

void IniConfig::SetEntry(const std::string &section, const std::string &key, const std::string &value) {
    m_values[section][key] = value;
}

void IniConfig::WriteChanges(const std::string &filename) const {
    std::ofstream outfile(filename);
    if (!outfile)
    {
        std::cerr << "Failed to write to output ini file " << filename << std::endl;
        return;
    }

    for (const auto &section : m_values)
    {
        const auto [name, vals] = section;
        outfile << "[" << name << "]" << "\n";

        for (const auto [key, value] : vals)
        {
            outfile << key << "=" << value << "\n";
        }
    }
    outfile.close();
}
