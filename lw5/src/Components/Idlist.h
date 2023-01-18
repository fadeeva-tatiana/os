#pragma once
#include "../Terminal.h"

void ParseIdlist(Buffer &buffer) {
    CompareItem(Terminal::ID, buffer);
    if (CheckItem(Terminal::COMMA, buffer)) {
        ParseIdlist(buffer);
    }
}
