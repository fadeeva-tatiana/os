#include "./CMiles.h"
#include <fstream>
#include <iostream>

const std::string MEALY_TO_MOORE = "mealy-to-moore";
const std::string MOORE_TO_MEALY = "moore-to-mealy";

enum class TransitionType {
    MilesToMura,
    MuraToMiles,
};

struct Args {
    TransitionType type;
    std::string input;
    std::string output;
};

TransitionType ParseType(const std::string &type) {
    if (type == MEALY_TO_MOORE) {
        return TransitionType::MilesToMura;
    }
    if (type == MOORE_TO_MEALY) {
        return TransitionType::MuraToMiles;
    }

    throw std::invalid_argument("Invalid type");
}

Args ParseArgs(int argc, char *argv[]) {
    if (argc != 4) {
        throw std::invalid_argument("Invalid argument count");
    }

    return {
            .type = ParseType(argv[1]),
            .input = argv[2],
            .output = argv[3],
    };
}

void CheckFileOpen(const std::ifstream &input, const std::ofstream &output) {
    if (!input.is_open()) {
        throw std::ios_base::failure("Error reading the file");
    }

    if (!output.is_open()) {
        throw std::ios_base::failure("Error writing the file");
    }
}

std::string ReadCSV(std::istream &istream) {
    std::string result;
    std::string line;
    while (std::getline(istream, line)) {
        result += line + "\n";
    }

    return result;
}

void PrintData(std::ostream &ostream, const std::string &str) {
    ostream << str;
}

void ConvertMilesToMura(std::istream &input, std::ostream &output) {
    auto csv = ReadCSV(input);

    CMiles miles;
    miles.FromCSV(csv);

    CMura mura;
    miles.ToMura(mura);
    PrintData(output, mura.ConvertToCSV());
}

void ConvertMuraToMiles(std::istream &input, std::ostream &output) {
    auto csv = ReadCSV(input);

    CMura mura;
    mura.FromCSV(csv);

    CMiles miles;
    mura.ToMiles(miles);
    PrintData(output, miles.ConvertToCSV());
}

void Convert(const std::string &inputFileName, const std::string &outputFileName, TransitionType type) {
    std::ifstream input(inputFileName);
    std::ofstream output(outputFileName);
    CheckFileOpen(input, output);

    if (type == TransitionType::MilesToMura) {
        ConvertMilesToMura(input, output);
    }
    if (type == TransitionType::MuraToMiles) {
        ConvertMuraToMiles(input, output);
    }
}

int main(int argc, char *argv[]) {
    try {
        auto args = ParseArgs(argc, argv);
        Convert(args.input, args.output, args.type);

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
