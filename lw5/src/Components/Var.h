#pragma once
#include "Idlist.h"
#include "Type.h"

void ParseVar(Buffer &buffer) {
    CompareItem(Terminal::VAR, buffer);
    ParseIdlist(buffer);
    CompareItem(Terminal::COLON, buffer);
    ParseType(buffer);
    CompareItem(Terminal::SEMICOLON, buffer);
}
