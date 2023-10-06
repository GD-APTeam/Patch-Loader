#include "SubPatchBytesCell.hpp"

SubPatchBytesCell* SubPatchBytesCell::create(const char* name, const CCSize& size) {
    return new SubPatchBytesCell(name, size);
}

SubPatchBytesCell::SubPatchBytesCell(const char* name, const CCSize& size) : SubPatchCell(name, size) { }

bool SubPatchBytesCell::init() {
    SimpleTextArea* textArea = SimpleTextArea::create("");

    return true;
}