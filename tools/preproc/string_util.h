#ifndef STRING_UTIL_H
#define STRING_UTIL_H

inline bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

#endif // STRING_UTIL_H
