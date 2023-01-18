#pragma once
#include "../Buffer.h"
#include "../Terminal.h"
#include "F.h"

void ParseT(Buffer &buffer) {
    ParseF(buffer);
    if (CheckItem(Terminal::MULTIPLY, buffer)) {
        ParseT(buffer);
    }
}
