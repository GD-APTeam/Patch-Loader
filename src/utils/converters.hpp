#pragma once

#include "../includes.hpp"

namespace converters {
    template<typename T, typename std::enable_if<std::is_base_of<CCObject, T>::value>::type* = nullptr>
    CCArray* toCCArray(std::vector<T>& vector) {
        CCArray* array = CCArray::create();

        for (T& object : vector) {
            array->addObject(&object);
        }

        return array;
    }

    std::vector<std::byte> toBytes(const size_t size, const int value);
}