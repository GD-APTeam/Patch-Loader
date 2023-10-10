#include "converters.hpp"

std::vector<std::byte> converters::toBytes(const size_t size, const int value) {
    std::vector<std::byte> bytes(size);

    for (size_t i = 0; i < size; i++) {
        bytes[i] = static_cast<std::byte>(value >> 8 * i & UINT8_MAX);
    }

    return bytes;
}

LPVOID converters::toAddress(const std::uintptr_t address, const std::vector<std::uintptr_t>& offsets) {
    void* realAddress = reinterpret_cast<void*>(address);

    for (const std::uintptr_t offset : offsets) {
        realAddress = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(realAddress) + offset);
    }

    return realAddress;
}