#pragma once
#include <iostream>
#include <optional>

struct Args {
    std::string input;
};

std::optional<Args> ParseArgs(int argc, char *argv[]) {
    if (argc != 2) {
        return std::nullopt;
    }

    return Args{argv[1]};
}
