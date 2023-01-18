#pragma once
#include "../Buffer.h"
#include "T.h"

void ParseExp(Buffer &buffer) {
    ParseT(buffer);
    if (CheckItem(Terminal::PLUS, buffer)) {
        ParseExp(buffer);
    }
}
