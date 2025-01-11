#pragma once

#include <string>
#include <iostream>
#include <map>
#include <fstream>

template<typename T> T from_string(const std::string &);

template<>
inline int from_string(const std::string &str)
{
    return std::stoi(str);
}

template<>
inline float from_string(const std::string &str)
{
    return std::stof(str);
}

template<>
inline std::string from_string(const std::string &str) { return str; }

template<>
inline bool from_string(const std::string &str)
{
    if (!str.length())
    {
        return false;
    }
    if (str[0] == 't' || str[0] == 'T')
    {
        return true;
    }
    else if (str[0] == 'f' || str[0] == 'F')
    {
        return false;
    }
    return false;
}

class IniConfig {
public:
    IniConfig(const std::string &filename);

    IniConfig();
    void Read(const std::string &filename);

    void Print(std::ostream &out) const;

    template<typename T>
    T TryGetValue(const std::string &section, const std::string &key, const T &def) {
        const auto sectionEntries = m_values.find(section);
        if (sectionEntries == m_values.cend())
        {
            return def;
        }

        const auto sectionOfEntries = sectionEntries->second;
        const auto maybeEntry       = sectionOfEntries.find(key);
        if (maybeEntry == sectionOfEntries.cend())
        {
            return def;
        }

        return from_string<T>(maybeEntry->second);
    }

    void SetEntry(const std::string &section, const std::string &key, const std::string &value);

    void WriteChanges(const std::string &filename) const;

private:

    std::map<std::string, std::map<std::string, std::string>> m_values;
};
