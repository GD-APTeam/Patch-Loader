#include "converters.hpp"

std::vector<std::byte> converters::toBytes(const size_t size, const int value) {
    std::vector<std::byte> bytes(size);

    for (size_t i = 0; i < size; i++) {
        bytes[i] = static_cast<std::byte>(value >> 8 * i & 0xFF);
    }

    return bytes;
}