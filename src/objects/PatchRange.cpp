#include "PatchRange.hpp"

PatchRange PatchRange::get(const JSON& object) {
    if (object.is_object()) {
        const JSON& start = object["start"];
        const JSON& end = object["end"];
        const JSON& size = object["size"];

        if (start.is_number() && end.is_number() && size.is_number_unsigned()) {
            const size_t sizeValue = size.get<size_t>();
            const int startValue = start.get<int>();
            const int endValue = end.get<int>();
            const int maxValue = 0x7FFFFFFF >> 8 * (4 - sizeValue);
            const int minValue = -maxValue - 1;

            if (sizeValue <= 4 && sizeValue > 0 && endValue > startValue && startValue >= minValue && endValue <= maxValue) {
                PatchRange range(true);

                range.m_start = startValue;
                range.m_end = endValue;
                range.m_size = sizeValue;

                return range;
            }
        }
    }

    return PatchRange(false);
}

PatchRange::PatchRange() : BasePatch(false) { }

PatchRange::PatchRange(const bool valid) : BasePatch(valid) { }

void PatchRange::apply(const LPVOID address, const int value) {
    std::vector<std::byte> bytes(this->m_size);
    int correctedValue = value;

    if (this->m_start < value) {
        correctedValue = this->m_start;
    } else if (this->m_end < value) {
        correctedValue = this->m_end;
    }

    for (size_t i = 0; i < this->m_size; i++) {
        bytes[i] = static_cast<std::byte>(correctedValue >> 8 * i & 0xFF);
    }

    WriteProcessMemory(GetCurrentProcess(), address, bytes.data(), this->m_size, nullptr);
}

void PatchRange::apply() { }

void PatchRange::revert() { }

JSON PatchRange::toJson() {
    JSON patch;

    patch["start"] = this->m_start;
    patch["end"] = this->m_end;
    patch["size"] = this->m_size;

    return patch;
}