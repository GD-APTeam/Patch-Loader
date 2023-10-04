#include "SubPatch.hpp"

SubPatch SubPatch::get(const JSON& object) {
    if (object.is_object() && object["label"].is_string() && object["address"].is_number_unsigned()) {
        const PatchRange range = PatchRange::get(object["range"]);
        SubPatch subPatch(true);

        if (range.m_isValid) {
            subPatch.m_type = PatchType::RANGE;
            subPatch.m_range = range;
            subPatch.m_original = std::vector<std::byte>(range.m_size);
        } else if (object.contains("bytes") && SubPatch::isValidBytes(object["bytes"])) {
            subPatch.m_type = PatchType::BYTES;
            subPatch.m_bytes = object["bytes"].get<std::vector<std::byte>>();
            subPatch.m_original = std::vector<std::byte>(subPatch.m_bytes.size());
        } else if (object.contains("color") && object["color"].is_boolean() && object["color"].get<bool>()) {
            subPatch.m_type = PatchType::COLOR;
            subPatch.m_original = std::vector<std::byte>(12);
        } else if (object.contains("checkbox") && object["checkbox"].is_boolean() && object["checkbox"].get<bool>()) {
            subPatch.m_type = PatchType::CHECKBOX;
            subPatch.m_original = std::vector<std::byte>(1);
        } else {
            return SubPatch(false);
        }

        subPatch.m_label = object["label"].get<std::string>();
        subPatch.m_cocos = object.value("cocos", false);
        subPatch.m_address = object["address"].get<std::uintptr_t>();
        subPatch.m_realAddress = reinterpret_cast<LPVOID>((subPatch.m_cocos ? gd::cocosBase : gd::base) + subPatch.m_address);

        ReadProcessMemory(gd::process, subPatch.m_realAddress, subPatch.m_original.data(), subPatch.m_original.size(), nullptr);

        return subPatch;
    } else {
        return SubPatch(false);
    }

}

bool SubPatch::isValidBytes(const JSON& bytes) {
    if (bytes.is_array() && bytes.size()) {
        for (const JSON& byte : bytes) {
            // If any byte is not a number or is greater than 0xFF, it will break memory when applied.
            if (!byte.is_number_unsigned() || byte > 0xFF) {
                return false;
            }
        }

        return true;
    } else {
        return false;
    }
}

SubPatch::operator JSON() {
    return JSON {
        { "label", this->m_label },
        { "bytes", this->m_bytes },
        { "address", this->m_address },
        { "cocos", this->m_cocos }
    };
}

SubPatch::SubPatch(const bool valid) : BasePatch(valid) { }

void SubPatch::apply() {
    WriteProcessMemory(gd::process, this->m_realAddress, this->m_bytes.data(), this->m_bytes.size(), nullptr);
}

void SubPatch::revert() {
    WriteProcessMemory(gd::process, this->m_realAddress, this->m_original.data(), this->m_original.size(), nullptr);
}