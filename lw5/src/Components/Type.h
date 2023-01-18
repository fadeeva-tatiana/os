#pragma once

void ParseType(Buffer &buffer) {
    if (CheckItem(Terminal::INT, buffer) || CheckItem(Terminal::FLOAT, buffer) || CheckItem(Terminal::BOOL, buffer) || CheckItem(Terminal::STRING, buffer)) {
        return;
    }
    throw std::invalid_argument("\nERROR: Invalid type! Unexpected \"" + buffer.GetOriginalItem() + "\"");
}
