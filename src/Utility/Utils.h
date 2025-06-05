//
// Created by Kurt Slagle on 6/4/25.
//

#pragma once

template<typename T>
T getUpperBitsValue(const T &value, int N) {
    return (value >> N);
}

template<typename T>
T getLowerBitsValue(const T &value, int N) {
    int mask = ~(~0 << N);
    return ((value << N) >> N) & mask;
}
