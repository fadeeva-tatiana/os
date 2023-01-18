#pragma once
#include "../Common.h"
#include "../Terminal.h"
#include "Listst.h"
#include "Var.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

void ParseProg(Buffer &buffer) {
    CompareItem(Terminal::PROG, buffer);
    CompareItem(Terminal::ID, buffer);
    ParseVar(buffer);
    CompareItem(Terminal::BEGIN, buffer);
    ParseListst(buffer);
    CompareItem(Terminal::END, buffer);
}
