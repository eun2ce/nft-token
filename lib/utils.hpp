#pragma once

#include <string>

using std::string;

namespace utils {
    uint64_t hash_str( const string &str ){
        return hash<string>{}(str);
    }
}
