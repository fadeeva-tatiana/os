#include "src/Args.h"
#include "src/Buffer.h"
#include "src/Components/Prog.h"
#include <fstream>
#include <queue>
#include <sstream>

std::string GetString(std::ifstream &input) {
    std::string result;
    std::string line;
    while (std::getline(input, line)) {
        std::string resultLine;
        for (size_t i = 0; i < line.size(); ++i) {
            auto item = line[i];
            if (item == ',' || item == ';' || item == '(' || item == ')' || item == '+' || item == '-' || item == '*') {
                resultLine.append(" " + getString(item) + " ");
                continue;
            }

            if (item == ':') {
                if (i == line.size() - 1) {
                    resultLine.append(" : ");
                    continue;
                }
                if (line[++i] == '=') {
                    resultLine.append(" := ");
                } else {
                    resultLine.append(" " + getString(item) + line[i] + " ");
                }
                continue;
            }
            resultLine.append(getString(item));
        }
        result.append(resultLine + ' ');
    }
    return result;
}

int main(int argc, char *argv[]) {
    auto args = ParseArgs(argc, argv);
    if (!args.has_value()) {
        std::cout << "No arguments" << std::endl;
        return 1;
    }

    std::ifstream input(args.value().input);
    auto data = GetString(input);
    std::stringstream ss(data);
    std::string op;
    std::queue<std::string> queue;
    while (ss >> op) {
        queue.push(op);
    }

    try {
        Buffer buffer(queue);
        ParseProg(buffer);
        std::cout << "The analysis is successful!" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
