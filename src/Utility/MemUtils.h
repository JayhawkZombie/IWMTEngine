//
// Created by Kurt Slagle on 5/4/25.
//

#pragma once

#include <algorithm>
#include <functional>

inline void safe_strcpy(char *dest,
                        size_t dest_max_size,
                        const char *src,
                        size_t src_len) {
    size_t size_to_copy = std::min(src_len, dest_max_size);
    std::memcpy(dest, src, size_to_copy);
    dest[size_to_copy] = '\0';
}
