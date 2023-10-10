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
            const int maxValue = INT32_MAX >> 8 * (4 - sizeValue);
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

PatchRange::operator JSON() {
    return {
        { "start", this->m_start },
        { "end", this->m_end },
        { "size", this->m_size }
    };
}

PatchRange::PatchRange() : BasePatch(false) { }

PatchRange::PatchRange(const bool valid) : BasePatch(valid) { }

void PatchRange::apply(const LPVOID address, const int value) {
    WriteProcessMemory(gd::process, address, converters::toBytes(this->m_size, std::min(std::max(this->m_start, value), this->m_end)).data(), this->m_size, nullptr);
}

void PatchRange::apply() { }

void PatchRange::revert() { }