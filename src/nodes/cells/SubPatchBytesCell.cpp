#include "SubPatchBytesCell.hpp"

SubPatchBytesCell* SubPatchBytesCell::create(const char* name, const CCSize& size) {
    return new SubPatchBytesCell(name, size);
}

SubPatchBytesCell::SubPatchBytesCell(const char* name, const CCSize& size) : SubPatchCell(name, size) { }

bool SubPatchBytesCell::init() {
    std::stringstream stream;

    stream << std::hex << std::setfill('0') << "0x" << std::uppercase << this->m_patch->m_address << ":";

    for (const std::byte& byte : this->m_patch->m_bytes) {
        stream << " 0x" << std::setw(2) << static_cast<int>(byte);
    }

    SimpleTextArea* textArea = SimpleTextArea::create(stream.str(), "bigFont.fnt", 0.3f, this->m_width - 20);

    textArea->setAnchorPoint(TOP_LEFT);
    textArea->setMaxLines(1);
    textArea->setColor(DISABLED_4B);
    textArea->setPosition({ 0, this->m_content->getContentSize().height });

    this->m_content->addChild(textArea);
    
    return true;
}